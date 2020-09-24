import java.util.*;

public class MusicGenre{
    int playNum = 0;
    ArrayList<int[]> musicList = new ArrayList<int[]>();

    //constructor
     public MusicGenre(int playNum, ArrayList<int[]> musicList) {
        this.playNum = playNum;
        this.musicList = musicList;
    }
    
    //getter 세팅
    public int getPlayNum(){
        return this.playNum;
    }
    
    public ArrayList<int[]> getMusicList(){
        return this.musicList;
    };
}

class MusicComparator implements Comparator<int[]> {
    //compare 함수 재정의 - playNum이 큰 순서대로, 같을 시 고유번호가 작은 순서대로
    @Override
    public int compare(int[] a, int[] b) {
        if(a[1] < b[1]){
            return 1;
        }
        else if(a[1] > b[1]){
            return -1;
        }
        else{
            if(a[0] < b[0])
                return -1;
            else if(a[0] > b[0])
                return 1;
            else
                return 0;
        }
    }
}

class Solution {
    public int[] solution(String[] genres, int[] plays) {   
        
        //key가 String, value가 MusicGenre 타입의 map 정의
        Map<String, MusicGenre> map = new HashMap<String, MusicGenre>();
        
        for(int i = 0; i<genres.length; i++){
            int totalPlay;
            ArrayList<int[]> list;
            
            MusicGenre mg = map.get(genres[i]);//map에서 장르 찾기
            if(mg == null){//없으면 새로 정의
                totalPlay = 0;
                list = new ArrayList<int[]>();
            }
            else{//있으면 mg에서 정보 받기
                totalPlay = mg.getPlayNum();
                list = mg.getMusicList();
            }
            
            int[] pair = {i, plays[i]};
            list.add(pair);//list에 pair 정보 추가
            MusicGenre nmg = new MusicGenre(totalPlay + plays[i], list);//MusicGenre 새로 정의
            map.put(genres[i], nmg);//정의한 것을 넣기, genres[i]가 이미 있다면 그대로 교체됨
        }
        
        //map의 value(MusicGenre)의 정보로 이뤄진 list 생성 및 playNum에 따라 오름차순 sort
        List<MusicGenre> musicList = new ArrayList<>(map.values());
        Collections.sort(musicList, Comparator.comparing(MusicGenre::getPlayNum).reversed());
        
        ArrayList<Integer> answer = new ArrayList<Integer>();
        
        //musicList 내의 list 정보를 sort한 후 play 수가 1,2번째로 많은 고유번호 추출 및 저장
        for(MusicGenre genre : musicList){
            Collections.sort(genre.musicList, new MusicComparator());
            answer.add(genre.musicList.get(0)[0]);
            if(genre.musicList.size() > 1)
                answer.add(genre.musicList.get(1)[0]);
        }
        
        //ArrayList를 int[]로 변환
        int[] result = answer.stream().mapToInt(i -> i).toArray();
        return result;
    }
}