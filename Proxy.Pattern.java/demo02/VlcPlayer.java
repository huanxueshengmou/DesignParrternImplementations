package designmodeadapter;

public class VlcPlayer implements AdvancedMediaPlayer{
    @Override
    public void playVlc(String filName) {
        System.out.println("播放vlc文件："+filName);
    }

    @Override
    public void olayMp4(String filName) {
//vlc格式，MP4不做具体实现
    }
}
