typedef struct
{
    int riga;
    int colonna;
} cella_t;

typedef enum
{
    SOPRA,
    SOTTO,
    DESTRA,
    SINISTRA
} direzione_t;

cella_t posizione_mela();

void muovi(direzione_t);

void gioca(int R, int C){
    if(R%2==0){
        for(int i=0; i<R*C; i++){
            for(int j=1; j<C; j++)
                muovi(DESTRA);
            for(int c=1; c<R; c++){
                muovi(SOTTO);
                for(int j=1; c%2==1&&j<C-1; j++)
                    muovi(SINISTRA);
                for(int j=1; c%2==0&&j<C-1; j++)
                    muovi(DESTRA);
            }

            muovi(SINISTRA);
            for(int j=1; j<R; j++)
                muovi(SOPRA);
        }
    }
    else{
        for(int i=0; i<R*C; i++){
            for(int j=1; j<R; j++)
                muovi(SOTTO);
            for(int c=1; c<C; c++){
                muovi(DESTRA);
                for(int j=1; c%2==1&&j<R-1; j++)
                    muovi(SOPRA);
                for(int j=1; c%2==0&&j<R-1; j++)
                    muovi(SOTTO);
            }

            muovi(SOPRA);
            for(int j=1; j<C; j++)
                muovi(SINISTRA);
        }
    }
}

