package designmodeadapter;

public class AudioPlayer implements MediaPlayer{
    private MediaPlayerAdapter mediaPlayerAdapter;
    @Override
    public void play(String audioType, String filName) {
        if(audioType.equalsIgnoreCase("mp3")){
            System.out.println("播放MP3文件："+filName);
        }else if(
            audioType.equalsIgnoreCase("vlc")
            ||
            audioType.equalsIgnoreCase("mp4")
        ){
            mediaPlayerAdapter=new MediaPlayerAdapter(audioType);
            mediaPlayerAdapter.play(audioType,filName);
        }
    }
}
