#ifndef MOTION_HPP
#define MOTION_HPP

#define DO_NOTHING -1

struct Motion {
    float rx;
    float ry;
    float rz;

    float tx;
    float ty;
    float tz;

    // 建構子
    Motion(float rx, float ry, float rz,
           float tx, float ty, float tz)
        : rx(rx), ry(ry), rz(rz),
          tx(tx), ty(ty), tz(tz) {}
};
#endif