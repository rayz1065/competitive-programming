#include <bits/stdc++.h>
#define MAXN 50005

using namespace std;

int m_grid_size;
int r_jerry, c_jerry;
int n_cats;
pair<int, int> cats[MAXN];

struct RectT {
    int r_min;
    int r_max_ex; // excluded
    int c_min;
    int c_max_ex; // excluded
};

bool is_point_within (RectT a, pair<int, int> b) {
    bool inters_r = a.r_min <= b.first && b.first < a.r_max_ex;
    bool inters_c = a.c_min <= b.second && b.second < a.c_max_ex;
    return inters_r && inters_c;
}

bool overlaps (RectT a, RectT b) {
    bool inters_r = a.r_min < b.r_max_ex && b.r_min < a.r_max_ex;
    bool inters_c = a.c_min < b.c_max_ex && b.c_min < a.c_max_ex;
    return inters_r && inters_c;
}

bool is_safe(vector<RectT> rects) {
    // does this intersect the destination?
    vector<RectT> safe = {
        { 0, 1, 0, m_grid_size },
        { m_grid_size - 1, m_grid_size, 0, m_grid_size },
        { 0, m_grid_size, 0, 1 },
        { 0, m_grid_size, m_grid_size - 1, m_grid_size },
    };
    for (auto rect: rects) {
        for (auto x: safe) {
            if (overlaps(rect, x)) {
                return true;
            }
        }
    }
    return false;
}

pair<RectT, RectT> cut_rows (RectT a, int top_side_r) {
    RectT bottom_side = { a.r_min, top_side_r, a.c_min, a.c_max_ex };
    RectT top_side = { top_side_r, a.r_max_ex, a.c_min, a.c_max_ex };
    return { bottom_side, top_side };
}

pair<RectT, RectT> cut_cols (RectT a, int right_side_c) {
    RectT left_side = { a.r_min, a.r_max_ex, a.c_min, right_side_c };
    RectT right_side = { a.r_min, a.r_max_ex, right_side_c, a.c_max_ex };
    return { left_side, right_side };
}

void visualize_rectangles (vector<RectT> rects) {
    vector<vector<int>> buffer(20, vector<int>(20));
    for (int i = 0; i < rects.size(); i++) {
        auto rect = rects[i];
        for (int r = rect.r_min; r < rect.r_max_ex; r++) {
            for (int c = rect.c_min; c < rect.c_max_ex; c++) {
                if (r >= buffer.size() || c >= buffer[r].size()) {
                    continue ;
                }
                buffer[r][c] = i + 1;
            }
        }
    }
    bool found = false;
    for (int r = buffer.size() - 1; r >= 0; r--) {
        cerr << r << " \t";
        for (int c = 0; c < buffer[r].size(); c++) {
            found = found || buffer[r][c];
            if (buffer[r][c]) cerr << buffer[r][c];
            else cerr << " ";
        }
        cerr << "\r\n"[found];
    }
    cerr << "\n";
}

vector<RectT> remove_degenerates(vector<RectT> &rects) {
    vector<RectT> res;
    for (auto rect: rects) {
        if (rect.r_min >= rect.r_max_ex || rect.c_min >= rect.c_max_ex) {
            continue ;
        }
        res.push_back(rect);
    }
    return res;
}

vector<RectT> rect_subtract (RectT a, RectT b) {
    // returns a - b
    vector<RectT> splits;
    b.r_min = max(b.r_min, a.r_min);
    b.c_min = max(b.c_min, a.c_min);
    b.r_max_ex = min(b.r_max_ex, a.r_max_ex);
    b.c_max_ex = min(b.c_max_ex, a.c_max_ex);

    if (b.r_min >= b.r_max_ex || b.c_min >= b.c_max_ex) {
        return { a };
    }

    pair<RectT, RectT> bottom_top;
    if (b.r_min == a.r_min) {
        bottom_top = cut_rows(a, b.r_max_ex);
    } else {
        bottom_top = cut_rows(a, b.r_min);
    }
    pair<RectT, RectT> bottom_lr;
    pair<RectT, RectT> top_lr;
    if (b.c_min == a.c_min) {
        bottom_lr = cut_cols(bottom_top.first, b.c_max_ex);
        top_lr = cut_cols(bottom_top.second, b.c_max_ex);
    } else {
        bottom_lr = cut_cols(bottom_top.first, b.c_min);
        top_lr = cut_cols(bottom_top.second, b.c_min);
    }

    auto tl = top_lr.first, tr = top_lr.second;
    auto bl = bottom_lr.first, br = bottom_lr.second;

    // cerr << "tl, tr, bl, br\n"; visualize_rectangles({ tl, tr, bl, br });
    // cerr << "b\n"; visualize_rectangles({ b });
    // cerr << is_point_within(b, { bl.r_min, bl.c_min }) << " " <<
    //         is_point_within(b, { br.r_min, br.c_min }) << " " <<
    //         is_point_within(b, { tl.r_min, tl.c_min }) << " " <<
    //         is_point_within(b, { tr.r_min, tr.c_min }) << "\n";

    if (!is_point_within(b, { bl.r_min, bl.c_min })) {
        splits.push_back(bl);
    }
    if (!is_point_within(b, { br.r_min, br.c_min })) {
        splits.push_back(br);
    }
    if (!is_point_within(b, { tl.r_min, tl.c_min })) {
        splits.push_back(tl);
    }
    if (!is_point_within(b, { tr.r_min, tr.c_min })) {
        splits.push_back(tr);
    }

    return remove_degenerates(splits);
}

vector<RectT> subtract_many(vector<RectT> &rects, RectT b) {
    vector<RectT> res;
    for (auto rect: rects) {
        auto splits = rect_subtract(rect, b);
        for (auto j: splits) {
            res.push_back(j);
        }
    }
    return res;
}

RectT rectangle_with_range (pair<int, int> p, int range) {
    return {
        max(0, p.first - range),
        min(m_grid_size, p.first + range + 1),
        max(0, p.second - range),
        min(m_grid_size, p.second + range + 1)
    };
}

enum ResT {
    CAUGHT,
    ESCAPED,
    UNDETERMINED,
};

ResT try_escape (int range) {
    vector<RectT> rects, all_animals;
    rects.push_back(rectangle_with_range({ r_jerry, c_jerry }, range));
    all_animals = rects;
    for (int i = 0; i < n_cats; i++) {
        rects = subtract_many(rects, rectangle_with_range(cats[i], range));
        all_animals.push_back(rectangle_with_range(cats[i], range));
    }
    if (rects.size() == 0) {
        return CAUGHT;
    }
    return is_safe(rects) ? ESCAPED : UNDETERMINED;
}

void tc () {
    cin >> r_jerry >> c_jerry >> n_cats;
    r_jerry--, c_jerry--;
    for (int i = 0; i < n_cats; i++) {
        cin >> cats[i].first >> cats[i].second;
        cats[i].first--, cats[i].second--;
    }
    int min_escape = INT_MAX >> 1;
    for (auto range: vector<int>({ r_jerry, m_grid_size - r_jerry - 1, c_jerry, m_grid_size - c_jerry - 1 })) {
        ResT res = try_escape(range);
        if (res == ESCAPED) {
            min_escape = min(min_escape, range);
        }
    }
    if (min_escape != INT_MAX >> 1) {
        cout << "ESCAPED " << min_escape << "\n";
        return ;
    }
    int range_l = 0, range_r = m_grid_size + 5, max_undetermined = -1;
    while (range_l <= range_r) {
        int range = (range_l + range_r) / 2;
        ResT res = try_escape(range);
        assert(res != ESCAPED);
        if (res == UNDETERMINED) {
            max_undetermined = range;
            range_l = range + 1;
        } else {
            range_r = range - 1;
        }
    }
    cout << "CAUGHT " << max_undetermined + 1 << "\n";
}

int main () {
    int t;
    cin >> m_grid_size >> t;
    while (t--) tc();
}
