package designmodeadapter;

public class Mp4Player implements AdvancedMediaPlayer{
    @Override
    public void playVlc(String filName) {
        //MP4格式，vlc不做具体实现
    }

    @Override
    public void olayMp4(String filName) {
        System.out.println("播放MP4文件："+filName);
    }
}
