package designmodePicture;

public class JpgImageViewer implements ImageViewer{
    private JpgViewer jpgViewer;

    public JpgImageViewer(JpgViewer jpgViewer) {
        this.jpgViewer = jpgViewer;
    }

    @Override
    public void display(String fileName) {
        jpgViewer.displayJpg(fileName);
    }
}
