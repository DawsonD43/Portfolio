/**
 * Created by Dawson Dauphinais and Christian Wittbrodt
 * <p>
 * This program will load a Mad Lib template from a file and allow the user to
 * input words based on the type of word the program prompts.
 * <p>
 * loadMadLib method opens a Mad Lib template file
 * <p>
 * fillMadLib method reads through the template and asks the user to enter a word or phrase of the type
 * specified in the angled brackets
 * <p>
 * printMadLib method prints the story to both the screen and an output file.
 * <p>
 * playMadLib method calls loadMadLib with the filename, then calls fillMadLib, then call printMadLib
 */

import java.io.File;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class MadLibs {

    ArrayList<String> template = new ArrayList<>();


    public void loadMadLib() {
        //reads in mad lib template
        Scanner inputFile = new Scanner(System.in);
        System.out.println("Enter 1 for Tarzan template or 2 for Wallet template. ");
        int choice = inputFile.nextInt();
        //decides what file it is based on user input of 1 or 2
        if (choice == 1) {
            try {


                File templateFile = new File("tarzan.dat");
                Scanner tScan = new Scanner(templateFile);
                while (tScan.hasNext()) {
                    String word = tScan.next();
                    template.add(word);
                }

            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }

        } else if (choice == 2) {
            try {


                File templateFile = new File("wallet.dat");
                Scanner tScan = new Scanner(templateFile);
                while (tScan.hasNext()) {
                    String word = tScan.next();
                    template.add(word);
                }

            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }

        }
    }


    public void fillMadLib() {

        //reads through the template and then asks for user input based on what's inside the brackets
        for (int i = 0; i < template.size(); i++) {
            String s = template.get(i);

            if (s.charAt(0) == '<') {
                s = s.substring(1, s.length() - 1);
                System.out.println("Enter a/an " + s + ":");
                Scanner scan = new Scanner(System.in);
                String input = scan.nextLine();
                template.set(i, input);
            }
        }
    }

    //prints the output file and the screen based on the story
    public void printMadLib() throws FileNotFoundException {
        Scanner out = new Scanner(System.in);
        System.out.println("Output File: ");
        String outfile = out.next();
        PrintWriter outpwt = new PrintWriter(outfile);
        String story = "";
        //checks for when the line has more than 40 characters, and then makes a new line if it does
        for (int i = 0; i < template.size(); i++) {
            story += (template.get(i) + " ");
            if (story.length() + template.get(i).length() > 40) {
                outpwt.println(story);
                System.out.print(story);
                System.out.println();
                story = "";
            }
            outpwt.print(template.get(i) + " ");

        }
        System.out.print(story);
        outpwt.println(story);
        out.close();
        outpwt.close();


    }

    private void playMadLib() throws FileNotFoundException {
        MadLibs mad = new MadLibs();
        mad.loadMadLib();
        mad.fillMadLib();
        mad.printMadLib();
    }

    //main method that runs the all the previous methods and gives you the final output
    public static void main(String[] args) throws FileNotFoundException {
        MadLibs testMad = new MadLibs();

        Scanner input = new Scanner(System.in);
        System.out.print("Enter 1 to begin.");
        String file = input.next();
        File inputFile = new File(file);
        testMad.playMadLib();

    }
}
