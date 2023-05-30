import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.File;
import java.util.*;

public class DocumentFormat
{
    public static String path = "./docs";
    public static String[] MDnames = {"solution.md", "algorithm.md"};

    public static void main(String args[])
    {
        iterateFiles();
    }

    public static void iterateFiles()
    {
        File dir = new File(path);
        showFiles(dir.listFiles());
    }

    public static void showFiles(File[] files) {
        for (File file : files) {
            if (file.isDirectory()) {
                //System.out.println("Directory: " + file.getAbsolutePath());
                showFiles(file.listFiles());
            } else {
                //System.out.println("File: " + file.getAbsolutePath());

                for(String MDname : MDnames) {
                    if(MDname.equals(file.getName())) {
                        formatMD(file);
                    }
                }
            }
        }
    }

    public static void formatMD(File file) {
        System.out.println("READ "+file.getPath());
        List<String> lines = readMD(file);

        for(int i=0; i<lines.size(); i++) {
            if(lines.get(i).contains("**")) System.out.println((i+1) + " : " + lines.get(i));
        }
        writeMD(file, lines);

        System.out.println("=============================");
    }

    public static List<String> readMD(File file) {
        List<String> lines = new ArrayList<String>();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(file));

            String line = null;
            while ((line = reader.readLine()) != null){
                lines.add(line);
            }

            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return lines;
    }

    public static void writeMD(File file, List<String> lines) {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(file, false));

            for(String line : lines) {
                writer.write(line);
                writer.newLine();
            }

            writer.flush();
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}