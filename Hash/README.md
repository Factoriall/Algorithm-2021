# HashMap

## 특징
- Key와 Value으로 구성된 Entry 객체를 저장하는 구조
- Value는 중복 저장이 가능하지만 Key는 중복 저장 불가능
- 같은 Key값으로 저장될 시 덮어씌워짐
- Hashing 사용, 많은 데이터를 검색하는 데 있어서 뛰어난 성능을 보임

## 라이브러리 제외 코드
~~~java
class Entry<K, V> {
    final K key;
    V value;
    Entry<K, V> next;

    //constructor: key, value 및 같은 배열 내 linkedList로 연결된 next 노드
    public Entry(K key, V value, Entry<K, V> next) {
        this.key = key;
        this.value = value;
        this.next = next;
    }
}

public class MyMap<K, V> {
    private Entry<K, V>[] buckets;
    private static final int INITIAL_CAPACITY = 1 << 4; // 16
    private int size = 0;

    //최초 용량 설정
    public MyMap() {
        this(INITIAL_CAPACITY);//Alternate constructor invocations, 아래 constructor 사용
    }
    public MyMap(int capacity) {
        this.buckets = new Entry[capacity];
    }

    //put 메서드: hash값을 구해 그 위치의 배열에 저장
    public void put(K key, V value) {
        Entry<K, V> entry = new Entry<>(key, value, null);
        int bucket = getHash(key) % getBucketSize();
        Entry<K, V> existing = buckets[bucket];
        if (existing == null) {//위치에 저장된 것이 없으면 그냥 저장
            buckets[bucket] = entry;
            size++;
        } else {//key가 중간에 존재하면 value값만 교체, 없을 시 맨 끝에 값 저장
            // compare the keys see if key already exists
            while (existing.next != null) {
                if (existing.key.equals(key)) {
                    existing.value = value;
                    return;
                }
                existing = existing.next;
            }
            if (existing.key.equals(key)) {
                existing.value = value;
            } else {
                existing.next = entry;
                size++;
            }
        }
    } 
    
    //get 메서드: key가 저장된 위치 찾아서 value 출력, 없음 null 출력
    public V get(K key) {
        Entry<K, V> bucket = buckets[getHash(key) % getBucketSize()];
        while (bucket != null) {
            if (bucket.key.equals(key)) {
                return bucket.value;
            }
            bucket = bucket.next;
        }
        return null;
    }
    
    //key가 저장된 객체의 고유 주소값 return
    public int getHash(K key){
        return key.hashCode();
    }
    
    //buckets의 size return
    public int getBucketSize(){
        return buckets.length;
    }
}
~~~
- 출처: https://dzone.com/articles/custom-hashmap-implementation-in-java

## 사용 사례

## 정의 방법
1. import java.util.Hashmap;
2. import java.util.Map;
3. HashMap<K, V> map = new HashMap<K, V>(); 통해 비어있는 HashMap 생성
  - () 안에 Integer, float 타입의 숫자를 넣어 초기 용량 및 load factor 지정
  - HashMap은 Map 인터페이스를 상속받은 것이므로 Map<K, V> map = new HashMap<K, V>();으로 선언 가능

## 사용 메서드
- map.put(K key, V value): key를 가지는 value 객체 값을 map에 추가
- map.get(k Key): key값을 가지는 item의 value 반환
- map.remove(K key): key값을 가지는 item 삭제
- map.clear(): map 안의 모든 item 삭제
- map.size(): map 안에 들어있는 item 개수 반환
- map.keySet(): map 안의 value를 제외한 모든 key의 set를 반환
- map.values(): map 안의 key를 제외한 모든 value의 set를 반환
- 내부의 모든 엔트리 가져오는 방법
~~~java
for ( Map.Entry<String, Tab> entry : hash.entrySet()) {
    String key = entry.getKey();
    Tab tab = entry.getValue();
    // do something with key and/or tab
}
~~~

## 문제 사이트 및 코드
- notArrivedPlayer.java(완주하지 못한 선수): https://programmers.co.kr/learn/courses/30/lessons/42576
- phoneNumberList.java(전화번호 목록): https://programmers.co.kr/learn/courses/30/lessons/42577
- camouflage.java(위장): https://programmers.co.kr/learn/courses/30/lessons/42578
- bestAlbum.java(베스트앨범): https://programmers.co.kr/learn/courses/30/lessons/42579
