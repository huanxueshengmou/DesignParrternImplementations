package designmodePicture;

public class PngImageViewer implements ImageViewer{
    private PngViewer pngViewer;

    public PngImageViewer(PngViewer pngViewer) {
        this.pngViewer = pngViewer;
    }

    @Override
    public void display(String fileName) {
        pngViewer.displayPng(fileName);
    }
}
