////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

public class HelloWorld
{
    static
    {
        System.loadLibrary("native_hello_world");
    }

    public static void main(String[] args)
    {
        new HelloWorld().helloWorld();
    }

    private native void helloWorld();
}
