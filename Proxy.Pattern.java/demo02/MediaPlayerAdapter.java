package designmodeadapter;

public class MediaPlayerAdapter implements MediaPlayer{
    private AdvancedMediaPlayer advancedMediaPlayer;
    public MediaPlayerAdapter(String audioType){
        if(audioType.equalsIgnoreCase("vlc")){
            advancedMediaPlayer=new VlcPlayer();
        }else if(audioType.equalsIgnoreCase("mp4")){
            advancedMediaPlayer=new Mp4Player();
        }
    }
    @Override
    public void play(String audioType, String filName) {
        if(audioType.equalsIgnoreCase("vlc")){
            advancedMediaPlayer.playVlc(filName);
        }else if(audioType.equalsIgnoreCase("mp4")){
            advancedMediaPlayer.olayMp4(filName);
        }
    }
}
