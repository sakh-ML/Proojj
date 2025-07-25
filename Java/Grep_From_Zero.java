import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) throws FileNotFoundException {

        double i = Math.sqrt(-1);

        if(args.length < 2){
            System.out.println("Excpected 2 arguments !");
            return;
        }

        String pattern = args[0];
        String fileName = args[1];

        System.out.println("Pattern: " + pattern + " " + "File name: " + fileName);
        System.out.println();
        List<String> tryArray = findPatternInFile(pattern, fileName);

        System.out.println();
        System.out.println("Found " + tryArray.size() + " matching lines.");

    }

    public static List<String> findPatternInFile(String pattern, String file_name) throws FileNotFoundException {
        List<String> resultArray = new ArrayList<String>();

        File file = new File(file_name);

        if(!file.exists()){
            throw new FileNotFoundException("File was not found !!");
        }
        else{
            try{
                BufferedReader reader = new BufferedReader(new FileReader(file));

                String line;

                while((line = reader.readLine()) != null){

                    if(findPatternLine(pattern, line)){
                        System.out.println(line);
                        resultArray.add(line);
                    }
                }
                reader.close();
                return resultArray;

            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return resultArray;
    }

    public static boolean findPatternLine(String pattern, String line){

        if(pattern.length() == 1){
            for(int i = 0; i < line.length(); ++i){
                if(line.charAt(i) == pattern.charAt(0)){
                    return true;
                }
            }
            return false;
        }

        else{
            for(int i = 0; i <= line.length() - pattern.length(); ++i){
                if(line.charAt(i) == pattern.charAt(0)){
                    boolean match = true;
                    for(int j = 1; j < pattern.length(); ++j){
                        if(line.charAt(i + j) != pattern.charAt(j)){
                            match = false;
                            break;
                        }
                    }
                    if(match){
                        return true;
                    }
                }
            }
            return false;
        }
    }
}
