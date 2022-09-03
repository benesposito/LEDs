struct CRGB {
    int r;
    int g;
    int b;

    CRGB() { }
    CRGB(int r, int g, int b) : r(r), g(g), b(b) { }

    void setHSV(int in_h, int in_s, int in_v)
    {
        double      hh, p, q, t, ff;
        long        i;

        if(in_s <= 0.0) {       // < is bogus, just shuts up warnings
            r = in_v;
            g = in_v;
            b = in_v;
        }
        hh = in_h;
        if(hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        i = (long)hh;
        ff = hh - i;
        p = in_v * (1.0 - in_s);
        q = in_v * (1.0 - (in_s * ff));
        t = in_v * (1.0 - (in_s * (1.0 - ff)));

        switch(i) {
        case 0:
            r = in_v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = in_v;
            b = p;
            break;
        case 2:
            r = p;
            g = in_v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = in_v;
            break;
        case 4:
            r = t;
            g = p;
            b = in_v;
            break;
        case 5:
        default:
            r = in_v;
            g = p;
            b = q;
            break;
        }   
    }
};

struct CHSV {
    int h;
    int s;
    int v;
};