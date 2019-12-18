#ifndef FFMPEG_H
#define FFMPEG_H

extern "C" {
#include <libavutil/pixfmt.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

#include <QImage>

class Ffmpeg
{
public:
    Ffmpeg();
    ~Ffmpeg();
    AVCodec * m_codec;
    AVCodecContext * m_context;

    int ffmpeg_init();
    void ffmpeg_free();

    QImage decode(unsigned char *avpkt_data, int avpkt_size, int width, int height);
};

#endif // FFMPEG_H
