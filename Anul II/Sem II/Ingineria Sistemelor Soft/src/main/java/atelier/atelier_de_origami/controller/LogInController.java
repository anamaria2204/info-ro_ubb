package atelier.atelier_de_origami.controller;

import atelier.atelier_de_origami.*;
import atelier.atelier_de_origami.domain.Student;
import atelier.atelier_de_origami.domain.Teacher;
import atelier.atelier_de_origami.service.Service;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.CheckBox;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class LogInController {
    Service service;
    Stage stage;

    @FXML
    TextField usernameField;
    @FXML
    PasswordField passwordField;
    @FXML
    CheckBox teacherCheckBox;

    public void setService(Service service) {
        this.service = service;
        System.out.println("LogInController: Received Service instance: " + service);
    }

    public void setDialogStage(Stage stage) {
        this.stage = stage;
    }

    @FXML
    private void handleSignInButton(){
        String username = usernameField.getText();
        String password = passwordField.getText();

        if(username.isEmpty() || password.isEmpty()){
            showAlert("Eroare", "Nu ati completat toate campurile!", Alert.AlertType.ERROR);
            return;
        }
        if(teacherCheckBox.isSelected()){
            Teacher teacher = service.getTeacherByUsername(username);
            if(teacher != null && teacher.getPassword().equals(password)){
                showTeacherWindow(teacher);
            } else {
                showAlert("Eroare", "Username sau parola gresita!", Alert.AlertType.ERROR);
            }
        } else {
            Student student = service.getStudentByUsername(username);
            if(student != null && student.getPassword().equals(password)){
                showStudentWindow(student);
            } else {
                showAlert("Eroare", "Username sau parola gresita!", Alert.AlertType.ERROR);
            }
        }
    }

    private void showTeacherWindow(Teacher teacher){
        try{
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/atelier/atelier_de_origami/teacher-view.fxml"));
            AnchorPane teacherLayout = fxmlLoader.load();
            Stage stage = new Stage();
            stage.setScene(new Scene(teacherLayout));

            TeacherController teacherController = fxmlLoader.getController();
            teacherController.setService(service, teacher);
            System.out.println("LogInController: Passed Service instance to TeacherController: " + service);
            service.addObserver(teacherController);
            teacherController.setDialogStage(stage);
            stage.setTitle("Hello, " + teacher.getFirstname() + "! <3");
            stage.show();

        } catch (IOException e) {
            e.printStackTrace();
            showAlert("Error", "Error at opening the teacher window", Alert.AlertType.ERROR);
        }
    }

    private void showStudentWindow(Student student){
        try{
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/atelier/atelier_de_origami/student-view.fxml"));
            AnchorPane studentLayout = fxmlLoader.load();
            Stage stage = new Stage();
            stage.setScene(new Scene(studentLayout));

            StudentController studentController = fxmlLoader.getController();
            studentController.setService(service, student);
            service.addObserver(studentController);
            System.out.println("LogInController: Passed Service instance to StudentController: " + service);
            studentController.setDialogStage(stage);
            stage.setTitle("Hi, " + student.getFirstname() + "! <3");
            stage.show();

        } catch (IOException e) {
            e.printStackTrace();
            showAlert("Eroare", "Eroare la deschiderea ferestrei principale", Alert.AlertType.ERROR);
        }
    }

    @FXML
    private void handleSignUpButton() {
        showSignUpWindow();
    }

    private void showSignUpWindow() {
       try{
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/atelier/atelier_de_origami/sign_up-view.fxml"));
            AnchorPane signUpLayout = fxmlLoader.load();
            Stage stage = new Stage();
            stage.setScene(new Scene(signUpLayout));

            SignUpController signUpController = fxmlLoader.getController();
            signUpController.setService(service);
            signUpController.setDialogStage(stage);
            stage.setTitle("Ready to be a part of creative corner? <3");
            stage.show();

        } catch (IOException e) {
            e.printStackTrace();
            showAlert("Error", "Error at opening the student window", Alert.AlertType.ERROR);
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
