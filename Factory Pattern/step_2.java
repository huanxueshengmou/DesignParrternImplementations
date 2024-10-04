public class step_2 {
  public abstract class Diren {
    public abstract void make();
}
public class DirenS extends S{
    public void make(){
        System.out.println("伤害为30");
    }
}
public class DirenShuxing implements Shuxing{
    private DirenX direnx=null;
    private DirenW direnw=null;
    private DirenS direns=null;


    @Override
    public DirenX getX() {
        direnx=new DirenX();
        return direnx;
    }

    @Override
    public DirenS getS() {
        direns=new DirenS();
        return direns;
    }

    @Override
    public DirenW getW() {
        direnw=new DirenW();
        return direnw;
    }
    public void make(){
        direns.make();
        direnw.make();
        direnx.make();
    }
}

public class DirenW extends W{
    public void make(){
        System.out.println("武器为刀");
    }
}
public class DirenX extends X{
    public void make(){
        System.out.println("血量为100");
    }
}
public class Goblin extends Diren {
    public void make(){
        System.out.println("创建了一个goblin类型的敌人");
    }
}
public class Goblin01 extends Xuanzeleixing{
    public Diren getdiren(){
        return new Goblin();
    }
}
public class Orc extends Diren{
    public void make(){
        System.out.println("创建了一个orc类型的敌人");
    }
}
public class Orc01 extends Xuanzeleixing{
    public Diren getdiren(){
        return new Orc();
    }
}
public abstract class S {
    public abstract void make();
}
public interface Shuxing {
    public DirenX getX();
    public DirenS getS();
    public DirenW getW();
}
public abstract class W {
    public abstract void make();
}

public abstract class X {
    public abstract void make();
}
public abstract class Xuanzeleixing {
    public abstract Diren getdiren();
}
// public class Text {
//     public static void main(String[] args) {
//         Goblin01 goblin01=new Goblin01();
//         Diren X=goblin01.getdiren();
//         X.make();

//         Orc01 orc01=new Orc01();
//         Diren Y=orc01.getdiren();
//         Y.make();

//         DirenShuxing s=new DirenShuxing();
//         s.getS();
//         s.getW();
// }
// }
}