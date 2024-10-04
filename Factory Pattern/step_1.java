public class step_1{
public abstract class Diren {
    public abstract void make();
}
public class Goblin extends Diren {
    public void make(){
        System.out.println("创建了一个goblin类型的敌人");
    }
}
public class Orc extends Diren{
    public void make(){
        System.out.println("创建了一个orc类型的敌人");
    }
}
public class Xuanzeleixing {
    public Diren getdiren(String diren) {
        if ("Goblin".equalsIgnoreCase(diren)) {
            return new Goblin();
        } else if ("Orc".equalsIgnoreCase(diren)) {
            return new Orc();
        }
            return null;
    }
}

// public static void main(String[] args) {
//     Xuanzeleixing X=new Xuanzeleixing();
//     Diren orc=X.getdiren("Orc");
//     orc.make();
// }

}