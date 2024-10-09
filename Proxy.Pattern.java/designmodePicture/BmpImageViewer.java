package designmodePicture;

public class BmpImageViewer implements ImageViewer{
    private BmpViewer bmpViewer;

    public BmpImageViewer(BmpViewer bmpViewer) {
        this.bmpViewer = bmpViewer;
    }

    @Override
    public void display(String fileName) {
        bmpViewer.displayBmp(fileName);
    }
}
