import java.util.Scanner; // Because we need to read the csv file
import java.io.*;

public class Grade {
    public static void main(String[] args) throws FileNotFoundException {
        // We use "File" to get the csv file.
        File getCSVFiles = new File("HW2data.csv");
        // Usw "Scanner" to read.
        Scanner sc = new Scanner(getCSVFiles);
        sc.useDelimiter(","); // Because the delimiter in csv is ','.
        // Because line 1 is the title name, we skip line 1
        String FileValue = sc.nextLine();
        int i = 0;
        while(sc.hasNext()){
            FileValue = sc.nextLine(); // Get nex line in the file
            // Splits a string at the specified regular expression and returns an array of substrings.
            String [] row = FileValue.split(",");
            // Calculate the score of the HW1~HW3 and turn it to double type.
            double hw = Double.parseDouble(row[3])*0.1 + Double.parseDouble(row[4])*0.1 + Double.parseDouble(row[5])*0.1;
            // Calculate the score of the Midtern and Final and then turn it to double type.
            double exam = Double.parseDouble(row[6])*0.3 + Double.parseDouble(row[7])*0.4;
            // Plus all score.
            double score = hw + exam;
            // Use round() function (四捨五入), becaus the range is integar, we need to round the score.
            if(Math.round(score) <= 49){
                i++;
                // "-" represtn to align left, number represent to the length of output data.
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                // "println" represtn to newline
                System.out.println(" " + String.format("%.2f", score) + "  E");
            }else if(Math.round(score) >= 50 && Math.round(score) <= 59){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  D");
            }else if(Math.round(score) >= 60 && Math.round(score) <= 62){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  C-");
            }else if(Math.round(score) >= 63 && Math.round(score) <= 66){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  C");
            }else if(Math.round(score) >= 67 && Math.round(score) <= 69){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  C+");
            }else if(Math.round(score) >= 70 && Math.round(score) <= 72){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  B-");
            }else if(Math.round(score) >= 73 && Math.round(score) <= 76){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  B");
            }else if(Math.round(score) >= 77 && Math.round(score) <= 79){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  B+");
            }else if(Math.round(score) >= 80 && Math.round(score) <= 84){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  A-");
            }else if(Math.round(score) >= 85 && Math.round(score) <= 89){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  A");
            }else if(Math.round(score) >= 90 && Math.round(score) <= 100){
                i++;
                System.out.print(String.format("%-3s",i) + String.format("%-9s",row[1]) + "  " + String.format("%-6s",row[2]));
                System.out.println(" " + String.format("%.2f", score) + "  A+");
            }
        }
        sc.close();  
    }
}
