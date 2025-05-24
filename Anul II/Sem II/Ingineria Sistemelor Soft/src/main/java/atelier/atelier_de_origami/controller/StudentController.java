package atelier.atelier_de_origami.controller;

import atelier.atelier_de_origami.domain.Booking;
import atelier.atelier_de_origami.domain.Course;
import atelier.atelier_de_origami.domain.Student;
import atelier.atelier_de_origami.events.ChangeEventType;
import atelier.atelier_de_origami.events.EntityChangeEvent;
import atelier.atelier_de_origami.observer.Observer;
import atelier.atelier_de_origami.service.Service;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.time.format.DateTimeFormatter;

public class StudentController implements Observer<EntityChangeEvent<?>> {
    Service service;
    Stage stage;
    Student student;

    ObservableList<Course> availableCoursesList = FXCollections.observableArrayList();
    ObservableList<Course> bookedCoursesList = FXCollections.observableArrayList();


    @FXML
    Label labelStudent;
    @FXML
    Label labelCourseAvailable;

    @FXML
    TableView<Course> tableViewCoursesAvailable;
    @FXML
    TableView<Course> tableViewCoursesBooked;

    @FXML
    TableColumn<Course, String> courseNameColumn;
    @FXML
    TableColumn<Course, String> courseDateColumn;
    @FXML
    TableColumn<Course, String> courseDurationColumn;
    @FXML
    TableColumn<Course, String> coursePriceColumn;
    @FXML
    TableColumn<Course, String> courseTeacherNameColumn;
    @FXML
    TableColumn<Course, String> courseDifficultyColumn;
    @FXML
    TableColumn<Course, String> courseSeatsColumn;

    @FXML
    TextField courseNameField;
    @FXML
    TextField courseDateField;
    @FXML
    TextField TeacherNameField;
    @FXML
    TextField dificultyField;

    @FXML
    TableColumn<Course, String> BcourseNameColumn;
    @FXML
    TableColumn<Course, String> BcourseDateColumn;
    @FXML
    TableColumn<Course, String> BcourseDurationColumn;
    @FXML
    TableColumn<Course, String> BcoursePriceColumn;
    @FXML
    TableColumn<Course, String> BcourseTeacherNameColumn;
    @FXML
    TableColumn<Course, String> BcourseDifficultyColumn;

    public void setService(Service service, Student student) {
        this.service = service;
        this.student = student;
        initModel();
    }
    public void setDialogStage(Stage stage) {
        this.stage = stage;
    }

    private void initModel() {
        labelStudent.setText("Hello " + student.getFirstname() + " " + student.getLastname() + "! <3");
        labelCourseAvailable.setText("Available courses for age: " + student.getAge() + " years");

        Iterable<Course> filteredCourses = service.getAllCoursesForAge(student.getAge());
        filteredCourses.forEach(availableCoursesList::add);

        if (courseNameColumn.getCellValueFactory() == null) {
            courseNameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getName()));
            courseDateColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    cellData.getValue().getDate().format(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm"))));
            courseDurationColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    String.valueOf(cellData.getValue().getDuration())));
            coursePriceColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    String.format("%.2f", cellData.getValue().getPrice())));
            courseTeacherNameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    cellData.getValue().getTeacher().getFirstname() + " " + cellData.getValue().getTeacher().getLastname()));
            courseDifficultyColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    cellData.getValue().getExperienceLevel().toString()));
            courseSeatsColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    String.valueOf(cellData.getValue().getMaxParticipants())));
        }

        tableViewCoursesAvailable.setItems(availableCoursesList);

        service.getAllCoursesBookedByStudent(student.getId()).forEach(bookedCoursesList::add);
        tableViewCoursesBooked.setItems(bookedCoursesList);

        // Setup columns if needed
        if (BcourseNameColumn.getCellValueFactory() == null) {
            BcourseNameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getName()));
            BcourseDateColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    cellData.getValue().getDate().format(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm"))));
            BcourseDurationColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    String.valueOf(cellData.getValue().getDuration())));
            BcoursePriceColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    String.format("%.2f", cellData.getValue().getPrice())));
            BcourseTeacherNameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    cellData.getValue().getTeacher().getFirstname() + " " + cellData.getValue().getTeacher().getLastname()));
            BcourseDifficultyColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                    cellData.getValue().getExperienceLevel().toString()));

            tableViewCoursesBooked.getSelectionModel().selectedItemProperty().addListener(
            (observable, oldValue, newValue) -> showCourseDetails(newValue));

        }
    }

    @FXML
    private void handleLogoutButton() {
        stage.close();
        service.removeObserver(this);
        showAlert("Logout", "See you again! <3", Alert.AlertType.INFORMATION);
    }

    private void showAlert(String title, String message, Alert.AlertType type){
        Alert alert = new Alert(type);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    @Override
    public void update(EntityChangeEvent<?> entityChangeEvent) {
        System.out.println(">>> StudentController a primit evenimentul: " + entityChangeEvent.getType());

        if (entityChangeEvent.getType() == ChangeEventType.BOOKCOURSE ||
            entityChangeEvent.getType() == ChangeEventType.ADDCOURSE ||
            entityChangeEvent.getType() == ChangeEventType.UPDATECOURSE ||
            entityChangeEvent.getType() == ChangeEventType.REMOVEBOOKING) {

            refreshAvailableCourses();
            refreshBookingsList();
        }
    }


    private void refreshAvailableCourses() {
        availableCoursesList.clear();
        service.getAllCoursesForAge(student.getAge()).forEach(availableCoursesList::add);
        tableViewCoursesAvailable.refresh();
    }

    private void showCourseDetails(Course course) {
        if (course != null) {
            courseNameField.setText(course.getName());
            courseDateField.setText(course.getDate().format(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm")));
            TeacherNameField.setText(course.getTeacher().getFirstname() + " " + course.getTeacher().getLastname());
            dificultyField.setText(course.getExperienceLevel().toString());

            courseNameField.setEditable(false);
            courseDateField.setEditable(false);
            TeacherNameField.setEditable(false);
            dificultyField.setEditable(false);
        }
    }

    private void refreshBookingsList(){
        bookedCoursesList.clear();
        service.getAllCoursesBookedByStudent(student.getId()).forEach(bookedCoursesList::add);
        tableViewCoursesBooked.refresh();
        clearCourseDetails();
    }

    @FXML
    private void handleBookingButton(){
        Course selectedCourse = tableViewCoursesAvailable.getSelectionModel().getSelectedItem();
        if (selectedCourse != null) {

            if(selectedCourse.getMaxParticipants() == 0){
                showAlert("Error", "No available seats for this course.", Alert.AlertType.ERROR);
                return;
            }
            Iterable<Booking> bookedCourses = service.getAllBookingStudent(student.getId());
            for (Booking booking : bookedCourses) {
                if (booking.getCourse().getId().equals(selectedCourse.getId())) {
                    showAlert("Error", "You have already booked this course.", Alert.AlertType.WARNING);
                    return;
                }
            }
            try {
                service.addBooking(student, selectedCourse);
                showAlert("Booking", "You have successfully booked the course: " + selectedCourse.getName(), Alert.AlertType.INFORMATION);

            } catch (Exception e) {
                showAlert("Error", e.getMessage(), Alert.AlertType.ERROR);
            }
        } else {
            showAlert("Error", "Please select a course to book.", Alert.AlertType.ERROR);
        }
    }

    @FXML
    private void handleDeleteBookingButton(){
        Course selectedCourse = tableViewCoursesBooked.getSelectionModel().getSelectedItem();
        if (selectedCourse != null) {
            try {
                service.deleteBooking(student, selectedCourse);
                showAlert("Booking", "You have successfully deleted the booking for the course: " + selectedCourse.getName(), Alert.AlertType.INFORMATION);

                clearCourseDetails();
            } catch (Exception e) {
                showAlert("Error", e.getMessage(), Alert.AlertType.ERROR);
            }
        } else {
            showAlert("Error", "Please select a course to delete the booking.", Alert.AlertType.ERROR);
        }
    }

    private void clearCourseDetails() {
        courseNameField.clear();
        courseDateField.clear();
        TeacherNameField.clear();
        dificultyField.clear();
    }

}
