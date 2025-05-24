package atelier.atelier_de_origami.controller;

import atelier.atelier_de_origami.domain.CourseCategory;
import atelier.atelier_de_origami.domain.ExperienceLevel;
import atelier.atelier_de_origami.domain.Student;
import atelier.atelier_de_origami.service.Service;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class SignUpController {
    Service service;
    Stage stage;

    @FXML
    private TextField nameField;
    @FXML
    private TextField surnameField;
    @FXML
    private TextField emailField;
    @FXML
    private TextField phoneField;
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;
    @FXML
    private TextField ageField;

    public void setService(Service service) {
        this.service = service;
    }
    public void setDialogStage(Stage stage) {
        this.stage = stage;
    }

    public void handleSignUpButton(){
        String name = nameField.getText();
        String surname = surnameField.getText();
        String email = emailField.getText();
        String phone = phoneField.getText();
        String username = usernameField.getText();
        String password = passwordField.getText();
        String age = ageField.getText();

        if (name.isEmpty() || surname.isEmpty() || email.isEmpty() || phone.isEmpty() || username.isEmpty() || password.isEmpty()) {
            showAlert("Error", "All fields must be filled!", Alert.AlertType.ERROR);
            return;
        }
        int age_i = Integer.parseInt(age);
        Student student = new Student(name, surname, age_i, phone, email, username, password);
        service.addStudent(student);
        showAlert("Success", "Account created successfully!", Alert.AlertType.INFORMATION);
        showStudentWindow(student);
        stage.close();

    }

    private void showStudentWindow(Student student){
        try{
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/atelier/atelier_de_origami/student-view.fxml"));
            AnchorPane studentLayout = fxmlLoader.load();
            Stage stage = new Stage();
            stage.setScene(new Scene(studentLayout));

            StudentController studentController = fxmlLoader.getController();
            studentController.setService(service, student);
            studentController.setDialogStage(stage);
            stage.setTitle("Hi, " + student.getFirstname() + "! <3");
            stage.show();

        } catch (IOException e) {
            e.printStackTrace();
            showAlert("Eroare", "Eroare la deschiderea ferestrei principale", Alert.AlertType.ERROR);
        }
    }

    private void showAlert(String title, String message, Alert.AlertType type){
        Alert alert = new Alert(type);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

}
