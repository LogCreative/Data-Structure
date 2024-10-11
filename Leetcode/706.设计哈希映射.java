import java.util.LinkedList;
import java.util.Iterator;

/*
 * @lc app=leetcode.cn id=706 lang=java
 *
 * [706] 设计哈希映射
 */

// @lc code=start

class MyHashMap {

    class Pair {
        private int key;
        private int value;

        public Pair(int k, int v) {
            key = k;
            value = v;
        }

        public int getKey() {
            return key;
        }

        public int getValue() {
            return value;
        }

        public void setValue(int v) {
            value = v;
        }
    }

    private static final int BASE=761;
    private LinkedList[] data;

    public MyHashMap() {
        data = new LinkedList[BASE];
        for (int i = 0; i < BASE; ++i) {
            data[i] = new LinkedList<Pair>();
        }
    }
    
    public void put(int key, int value) {
        int pos = hash(key);
        Iterator<Pair> it = data[pos].iterator();
        while(it.hasNext()) {
            Pair pair = it.next();
            if (pair.getKey()==key) {
                pair.setValue(value);
                return ;
            }
        }
        data[pos].offerLast(new Pair(key, value));
    }
    
    public int get(int key) {
        int pos = hash(key);
        Iterator<Pair> it = data[pos].iterator();
        while(it.hasNext()) {
            Pair pair = it.next();
            if (pair.getKey()==key) {
                return pair.value;
            }
        }
        return -1;
    }
    
    public void remove(int key) {
        int pos = hash(key);
        Iterator<Pair> it = data[pos].iterator();
        while(it.hasNext()) {
            Pair pair = it.next();
            if (pair.getKey()==key) {
                data[pos].remove(pair);
                return ;
            }
        }
    }

    private int hash(int key){
        return key % BASE;
    }
}

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */
// @lc code=end

