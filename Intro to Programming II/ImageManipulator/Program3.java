import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.*;
import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * The purpose of this program is to create a
 * JavaFx program that will allow the user to load in a PPM
 * file and modify it using various methods, and then allows them
 * to save to a new file and clear their workspace.
 *
 * @author Dawson Dauphinais
 * CS1122, Fall 2018
 * <p>
 * Date Last Modified: 10 / 15 / 2018
 */
public class Program3 extends Application implements Program3Interface {

    /**
     * Main method that isn't necessary for JavaFX,
     * but is included in case start method isn't executed.
     *
     * @param args - program arguments
     */
    public static void main(String[] args) {
        launch(args);
    }

    /**
     * Loads in an image given the file provided by the user
     * to manipulate
     *
     * @param filename - the name of the file that will be loaded in
     *                 by the user for modification
     * @return the image that has been loaded in from the user's file
     * directory
     * @throws FileNotFoundException
     */
    @Override
    public WritableImage loadImage(String filename) throws FileNotFoundException {

        File inputFile = new File(filename);
        Scanner scan = new Scanner(inputFile);

        scan.next();
        String stop = scan.next();

        if (stop.charAt(0) == '#') {
            scan.nextLine();
        }

        int width = scan.nextInt();
        int height = scan.nextInt();
        scan.nextInt();

        WritableImage image = new WritableImage(width, height);
        PixelWriter show = image.getPixelWriter();

        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                int red = scan.nextInt();
                int blue = scan.nextInt();
                int green = scan.nextInt();

                Color pixColor = Color.rgb(red, blue, green);
                show.setColor(x, y, pixColor);

            }
        }

        return image;

    }

    /**
     * @param filename - the name of the file from which the image is
     *                 being loaded.
     * @param image    - the image that has been modified and will be
     *                 saved by the user.
     * @throws FileNotFoundException
     */
    @Override
    public void saveImage(String filename, WritableImage image) throws FileNotFoundException {

        PixelReader reader = image.getPixelReader();
        int width = (int) image.getWidth();
        int height = (int) image.getHeight();

        try {
            PrintWriter writer = new PrintWriter(new FileWriter(filename));
            writer.println("p");
            writer.println("#");
            writer.println(width + " " + height);
            writer.println(255);

            for (int x = 0; x < image.getWidth(); x++) {
                for (int y = 0; y < image.getHeight(); y++) {
                    Color color = reader.getColor(x, y);
                    int redPixel = (int) (color.getRed() * 255);
                    int greenPixel = (int) (color.getGreen() * 255);
                    int bluePixel = (int) (color.getBlue() * 255);
                    writer.printf("%03d %03d %03d", redPixel, greenPixel, bluePixel);
                }
                writer.println();
            }

            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Save file not found! ");
        }


    }

    /**
     * Inverts the image by using the setColor method and then
     * the invert command.
     *
     * @param image - the image to be inverted, do not modify!
     * @return a new image that has been inverted
     */

    @Override
    public WritableImage invertImage(WritableImage image) {

        PixelReader reader = image.getPixelReader();
        WritableImage wrtImage = new WritableImage((int) image.getWidth(), (int) image.getHeight());
        PixelWriter writer = wrtImage.getPixelWriter();

        for (int x = 0; x < image.getWidth(); x++) {
            for (int y = 0; y < image.getHeight(); y++) {
                writer.setColor(x, y, reader.getColor(x, y).invert());
            }
        }
        return wrtImage;
    }

    /**
     * Converts image into grayscale by changing the values of
     * the red, green, and blue pixels, and then multiplies them
     * by the luminescence value.
     *
     * @param image - the image to be converted to grayscale, do not modify!
     * @return a new image that has been converted to grayscale
     */

    @Override
    public WritableImage grayifyImage(WritableImage image) {

        WritableImage wrtImg = new WritableImage((int) image.getWidth(), (int) image.getHeight());
        PixelWriter writer = wrtImg.getPixelWriter();

        for (int x = 0; x < image.getWidth(); x++) {
            for (int y = 0; y < image.getHeight(); y++) {
                Color color = image.getPixelReader().getColor(x, y);
                int red = (int) (color.getRed() * 255);
                int green = (int) (color.getGreen() * 255);
                int blue = (int) (color.getBlue() * 255);
                int luminescence = (int) ((.2989 * red) + (.5870 * green) + (.1140 * blue));
                Color grayScale = Color.rgb(luminescence, luminescence, luminescence);
                writer.setColor(x, y, grayScale);

            }
        }
        return wrtImg;
    }


    /**
     * Pixelates the image by dividing it into 5 x 5 regions,
     * then assigns all pixels in the region the same color as
     * the central pixel
     *
     * @param image - the image to be pixelated
     * @return a new image that displays pixelated
     */
    @Override
    public WritableImage pixelateImage(WritableImage image) {

        int x = 0;

        PixelReader reader = image.getPixelReader();
        WritableImage wrtImg = new WritableImage((int) image.getWidth(), (int) image.getHeight());
        PixelWriter writer = wrtImg.getPixelWriter();


        for (; x < image.getWidth() - (image.getWidth() % 5); x += 5) {
            for (int y = 0; y < image.getHeight() - (image.getHeight() % 5); y += 5) {
                Color center = reader.getColor(x + 2, y + 2);

                for (int w = x; w < x + 5; w++) {
                    for (int z = y; z < y + 5; z++) {
                        writer.setColor(w, z, center);
                    }
                }
            }
        }
        if (image.getWidth() % 5 != 0) {
            for (int y = 0; y < image.getHeight() - (image.getHeight() % 5); y++) {
                Color center;
                if (image.getWidth() % 5 == 4) {
                    center = reader.getColor(x + 2, y + 2);
                } else {
                    center = reader.getColor((int) (image.getWidth() % 5) - 2 + x, y + 2);

                }
                for (int w = x; w < x + image.getWidth() % 5; w++) {
                    for (int z = y; z < y + 5; z++) {
                        writer.setColor(w, z, center);
                    }
                }
            }
        }
        return wrtImg;
    }

    /**
     * Flips the picture upside-down by changing the position of each pixel
     *
     * @param image - the image to be flipped, do not modify!
     * @return a new image that has been flipped
     */
    @Override
    public WritableImage flipImage(WritableImage image) {
        PixelReader reader = image.getPixelReader();
        WritableImage wrImage = new WritableImage((int) image.getWidth(), (int) image.getHeight());
        PixelWriter writer = wrImage.getPixelWriter();

        for (int x = 0; x < image.getWidth(); x++) {
            for (int y = 0; y < image.getHeight(); y++) {
                writer.setColor(x, y, reader.getColor(x, (int) image.getHeight() - 1 - y));
            }
        }
        return wrImage;
    }

    /**
     * Runs all of the above methods by assigning them
     * to buttons that are able to be clicked by the user
     *
     * @param primaryStage - the window that will pop up
     *                     and create the workspace for the user
     */
    public void start(Stage primaryStage) {
        BorderPane borderPane = new BorderPane();
        Scene scene = new Scene(borderPane, 800, 650);
        HBox statArea = new HBox();
        statArea.setPadding(new Insets(5));
        Label title = new Label("Image Manipulator - Intator ");

        primaryStage.setTitle("Image Manipulator - Inator");

        statArea.getChildren().addAll(title);
        title.setAlignment(Pos.TOP_CENTER);


        Label newLabel = new Label();
        borderPane.setCenter(newLabel);

        ImageView view = new ImageView();
        newLabel.setGraphic(view);

        HBox userButtons = new HBox(10);
        userButtons.setPadding(new Insets(10));
        borderPane.setBottom(userButtons);
        userButtons.setAlignment(Pos.BOTTOM_CENTER);

        Button loadFileButton = new Button("Load File");
        loadFileButton.setOnAction(event -> {
            try {
                FileChooser chooser = new FileChooser();
                File loadFile = chooser.showOpenDialog(primaryStage);
                if (loadFile != null) {
                    String name = loadFile.toString();
                    view.setImage(loadImage(name));

                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
                System.out.println("File Not Found");
            }
        });

        Button saveFileButton = new Button("Save File");
        saveFileButton.setOnAction(event -> {
            FileChooser chooseSave = new FileChooser();
            chooseSave.setTitle("Open Source File");
            String fileLocation = String.valueOf(chooseSave.showSaveDialog(primaryStage));

            try {
                saveImage(fileLocation, (WritableImage) view.getImage());

            } catch (FileNotFoundException exception) {
                exception.printStackTrace();
                System.out.println("File Not Found");
            }
        });

        Button clearImageButton = new Button("Clear Image");
        clearImageButton.setOnAction(event -> {
            PixelWriter writer = ((WritableImage) view.getImage()).getPixelWriter();
            for (int x = 0; x < ((WritableImage) view.getImage()).getWidth(); x++) {
                for (int y = 0; y < ((WritableImage) view.getImage()).getHeight(); y++) {
                    Color color = Color.rgb(255, 255, 255);
                    writer.setColor(x, y, color);
                }
            }
        });

        Button flipImageButton = new Button("Flip Image");
        flipImageButton.setOnAction(event -> {
            view.setImage(flipImage((WritableImage) view.getImage()));
            newLabel.setText("");
            newLabel.setGraphic(view);
        });

        Button invertImageButton = new Button("Invert Image");
        invertImageButton.setOnAction(event -> {
            view.setImage(invertImage((WritableImage) view.getImage()));
            newLabel.setText("");
            newLabel.setGraphic(view);
        });

        Button grayImageButton = new Button("Grayscale");
        grayImageButton.setOnAction(event -> {
            view.setImage(grayifyImage((WritableImage) view.getImage()));
            newLabel.setText("");
            newLabel.setGraphic(view);
        });

        Button pixelateImageButton = new Button("Pixelate Image");
        pixelateImageButton.setOnAction(event -> {
            view.setImage(pixelateImage((WritableImage) view.getImage()));
            newLabel.setText("");
            newLabel.setGraphic(view);
        });


        userButtons.getChildren().addAll(loadFileButton, saveFileButton, flipImageButton, invertImageButton,
                grayImageButton, pixelateImageButton, clearImageButton);

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
