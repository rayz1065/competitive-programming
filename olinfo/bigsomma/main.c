#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <linux/aio_abi.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

#pragma GCC optimize("O4")

#define BUFFER_SIZE (1<<16)
#define HALF_BUFFER (1<<15)

char buffer[BUFFER_SIZE + 20];
int io_setup(unsigned nr, aio_context_t *ctxp) {
	return syscall(__NR_io_setup, nr, ctxp);
}

int io_destroy(aio_context_t ctx) {
	return syscall(__NR_io_destroy, ctx);
}

int io_submit(aio_context_t ctx, long nr, struct iocb **iocbpp) {
	return syscall(__NR_io_submit, ctx, nr, iocbpp);
}

int io_getevents(aio_context_t ctx, long min_nr, long max_nr,
		struct io_event *events, struct timespec *timeout) {
	return syscall(__NR_io_getevents, ctx, min_nr, max_nr, events, timeout);
}

long long somma(FILE *f) {
    // fill up the entire buffer
    int fd = fileno(f);

	struct iocb cb_first, cb_second;
    int ret;
    memset(&cb_first, 0, sizeof(cb_first));
    cb_first.aio_buf = (uint64_t) buffer;
    cb_first.aio_offset = 0;
    cb_first.aio_nbytes = HALF_BUFFER;
    cb_first.aio_fildes = fd;
    cb_first.aio_lio_opcode = IOCB_CMD_PREAD;

    memset(&cb_second, 0, sizeof(cb_second));
    cb_second.aio_buf = (uint64_t) (buffer + HALF_BUFFER);
    cb_second.aio_offset = HALF_BUFFER;
    cb_second.aio_nbytes = HALF_BUFFER;
    cb_second.aio_fildes = fd;
    cb_first.aio_lio_opcode = IOCB_CMD_PREAD;

	struct iocb *cbs_first[1], *cbs_second[1];
    cbs_first[0] = &cb_first;
    cbs_second[0] = &cb_second;

    struct io_event events[1];
    aio_context_t aio_context;
    aio_context = 0;
    io_setup(1, &aio_context);

    ret = io_submit(aio_context, 1, cbs_first);
    ret = io_getevents(aio_context, 1, 1, events, NULL);
    ret = io_submit(aio_context, 1, cbs_second);
    ret = io_getevents(aio_context, 1, 1, events, NULL);

    int offset = BUFFER_SIZE;

    char last_read = 1;
    int i = 0;

    int n = 0;
    while (buffer[i] != '\n') {
        n = n * 10 + buffer[i++] - '0';
    }
    i++;

    long long sum = 0;
    while (n--) {
        int v = 0;
        char minus = (buffer[i] == '-');
        i+= minus;
        while (buffer[i] >= '0') {
            v = (v << 3) + (v << 1) + buffer[i++] - '0';
        }
        i++;
        sum+= (1 - (minus << 1)) * v;

        if (i & BUFFER_SIZE) {
            // printf("reading second half %d\n", i);
            // fill up the second half
            i -= BUFFER_SIZE;

            cb_second.aio_offset = offset;
            ret = io_submit(aio_context, 1, cbs_second);
            ret = io_getevents(aio_context, 1, 1, events, NULL);
            offset+= HALF_BUFFER;
            // for (int j = 0; j < BUFFER_SIZE; j++) {
            //     printf("%c", buffer[j]);
            // }
            // printf("\n");
            // if (n < 50000000 - 500)
            // return 0;

            last_read = 1; // last read is second half
        }
        else if ((i & HALF_BUFFER) && last_read) {
            // printf("reading first half %d\n", n);
            // fill up the first half of the buffer with new data
            
            cb_first.aio_offset = offset;
            ret = io_submit(aio_context, 1, cbs_first);
            ret = io_getevents(aio_context, 1, 1, events, NULL);
            offset+= HALF_BUFFER;
            // for (int j = 0; j < BUFFER_SIZE; j++) {
            //     printf("%c", buffer[j]);
            // }
            // printf("\n");

            last_read = 0; // last read is the first half
            for (int j = 0; j < 15; j++) {
                // copy the first data at the end of the buffer
                buffer[BUFFER_SIZE + j] = buffer[j];
            }
        }
    }
    
    return sum;
}
