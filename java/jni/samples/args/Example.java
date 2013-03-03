public class Example {
    public static void main(String[] args) {
        System.loadLibrary("Foo");

        Foo f = new Foo();

        f.sendInt(120);
        f.sendString("Hello!");

        String[] ss = {"abc", "def", "ghi"};
        f.sendStrings(ss);
    }
}

