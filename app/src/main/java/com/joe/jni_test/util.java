package com.joe.jni_test;

import android.util.Log;

/**
 * Created by david on 22/03/2018.
 */

public class util {
    final String TAG = "util";
    public int val;
    public String str;

    public class people {
        public int mage;
        private String mname;

        public people() {
            mage = 0;
            mname = "nobody";
        }

        public people(int nage, String name) {
            mage = nage;
            mname = name;
        }
        public void listou_info() {
            Log.d(TAG, "name: "+mname+", age:"+mage);
        }
    }

    private people mple;

    public util() {
        mple = new people();
    }

    public util(int age, String name) {
        mple = new people(age, name);
    }

    public void list_info() {
        mple.listou_info();
    }

    public people getPeopleObj() {
        return mple;
    }

}
