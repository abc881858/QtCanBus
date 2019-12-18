#include "ffmpeg.h"
#include <QDebug>
#include <QTime>

Ffmpeg::Ffmpeg()
{
    m_codec = nullptr;
    m_context = nullptr;

    ffmpeg_init();
}

Ffmpeg::~Ffmpeg()
{
    ffmpeg_free();
}

//初始化解码器 AV_CODEC_ID H264是AV_CODEC_ID_H264, H265是AV_CODEC_ID_HEVC, 具体看ffmpeg源码中的宏定义
int Ffmpeg::ffmpeg_init()
{
    m_codec = avcodec_find_decoder(AV_CODEC_ID_HEVC);
    m_context = avcodec_alloc_context3(m_codec);
    m_context->active_thread_type = FF_THREAD_FRAME;

    int avcodecopenRes = avcodec_open2(m_context, m_codec, nullptr);
    if (avcodecopenRes < 0)
    {
        if (m_context)
        {
            av_free(m_context);
            m_context = nullptr;
            return -1;
        }
    }

    return 0;
}

//解码, 把原始的H264/H265视频帧数据传入，得到解码后的YUV数据
/*
解码后的yuv数据在AVFrame *m_pic之中
m_pic->width 表示视频画面的像素宽度
m_pic->height 表示视频画面的像素高度
m_pic->format 表示yuv的格式，如比YUV420、YUV422、YUV444等，具体看ffmpeg源码中的枚举enum AVPixelFormat已经相关宏定义
m_pic->data[3] 表示解码后的yuv数据中元素data[0]、data[1]、data[2]分别表示Y、U、V
m_pic->linesize[3] 表示解码后的Y、U、V数据每行的size，linesize[0]、linesize[1]、linesize[2]分别表示Y、U、V
*/

//释放解码器
void Ffmpeg::ffmpeg_free()
{
    if (m_codec && m_context)
    {
        m_codec->close(m_context);
        m_codec = nullptr;
    }
    if (m_context)
    {
        avcodec_close(m_context);
        av_free(m_context);
    }

    m_codec = nullptr;
    m_context = nullptr;
}

QImage Ffmpeg::decode(unsigned char *avpkt_data, int avpkt_size, int width, int height)
{
//    qDebug() << QTime::currentTime() << "decode in";
    QImage image;
    AVPacket avpkt;
    memset(&avpkt, 0, sizeof(AVPacket));
    avpkt.data = avpkt_data;
    avpkt.size = avpkt_size;

    AVFrame *m_pic = av_frame_alloc();
    AVFrame *frameRGB = av_frame_alloc();

    avcodec_send_packet(m_context, &avpkt);
    avcodec_receive_frame(m_context, m_pic);

    av_image_alloc(frameRGB->data, frameRGB->linesize, width, height, AV_PIX_FMT_RGB24, 1);

    struct SwsContext* convert_ctx = nullptr;
    convert_ctx = sws_getContext(width, height, AV_PIX_FMT_YUV420P, width, height, AV_PIX_FMT_RGB24, SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);

    if(convert_ctx != nullptr)
    {
        sws_scale(convert_ctx, m_pic->data, m_pic->linesize, 0, height, frameRGB->data, frameRGB->linesize);
        sws_freeContext(convert_ctx);
        convert_ctx = nullptr;

        image = QImage(frameRGB->data[0], width, height, frameRGB->linesize[0], QImage::Format_RGB888);
        image.convertTo(QImage::Format_RGBA8888);
    }

    av_freep(&frameRGB->data[0]);
    av_frame_free(&frameRGB);
    av_frame_free(&m_pic);

//    qDebug() << QTime::currentTime() << "decode out";
    return image;
}
