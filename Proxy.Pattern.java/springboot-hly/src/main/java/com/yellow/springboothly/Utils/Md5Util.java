package com.yellow.springboothly.Utils;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Md5Util {
    protected static char hexDigits[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    protected static MessageDigest messageDigest=null;
    static {
        try{
            messageDigest=MessageDigest.getInstance("MD5");

        }catch (NoSuchAlgorithmException nseax){
            System.out.println(Md5Util.class.getName()+"初始化失败.messagedigest不支持md5util.");
            nseax.printStackTrace();
        }
    }

    public static String getMD5String(String s){return null;}
}
