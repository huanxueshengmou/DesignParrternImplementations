package GameA;

public class MinBoosDwarves implements MinBoos{
    @Override
    public BlacklronProperty createBlacklron() {
        System.out.print("黑铁矮人：");
        return new BlacklronDwarves();
    }

    @Override
    public SilverProperty createSilver() {
        System.out.print("白银矮人:");
        return new SilverDwarves();
    }
}
