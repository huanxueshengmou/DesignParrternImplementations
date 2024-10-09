package designmodePicture;

public class Test {
    public static void main(String[] args) {
        ImageViewer jpg=new JpgImageViewer(new JpgViewer());
        jpg.display("蕉太狼");

        ImageViewer bmp=new BmpImageViewer(new BmpViewer());
        bmp.display("懒羊羊大王");

        ImageViewer png=new PngImageViewer(new PngViewer());
        png.display("灰太狼");
    }
}
