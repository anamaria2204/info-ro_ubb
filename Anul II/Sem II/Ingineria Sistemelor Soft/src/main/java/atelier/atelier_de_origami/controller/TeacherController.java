package atelier.atelier_de_origami.controller;

import atelier.atelier_de_origami.domain.*;
import atelier.atelier_de_origami.events.ChangeEventType;
import atelier.atelier_de_origami.events.EntityChangeEvent;
import atelier.atelier_de_origami.observer.Observer;
import atelier.atelier_de_origami.service.Service;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class TeacherController implements Observer<EntityChangeEvent<?>> {
    Service service;
    Stage stage;
    Teacher teacher;
    ObservableList<Course> courseList = FXCollections.observableArrayList();
    ObservableList<Student> studentList = FXCollections.observableArrayList();


    @FXML
    Label welcomeLabel;
    @FXML
    Label tableStudentLabel;
    @FXML
    ComboBox<String> ageComboBox;
    @FXML
    ComboBox<String> experienceComboBox;

    @FXML
    TextField courseNameField;
    @FXML
    TextField courseDateField;
    @FXML
    TextField courseDurationField;
    @FXML
    TextField coursePriceField;
    @FXML
    TextField courseMaxParticipantsField;

    @FXML
    TableView<Course> courseTableView;
    @FXML
    TableColumn<Course, String> courseNameColumn;
    @FXML
    TableColumn<Course, String> courseDateColumn;
    @FXML
    TableColumn<Course, String> courseDurationColumn;
    @FXML
    TableColumn<Course, String> coursePriceColumn;
    @FXML
    TableColumn<Course, String> courseCategoryColumn;
    @FXML
    TableColumn<Course, String> courseExperienceLevelColumn;
    @FXML
    TableColumn<Course, String> courseMaxParticipantsColumn;

    @FXML
    TableView<Student> studentTableView;
    @FXML
    TableColumn<Student, String> studentFirstNameColumn;
    @FXML
    TableColumn<Student, String> studentLastNameColumn;
    @FXML
    TableColumn<Student, String> studentAgeColumn;
    @FXML
    TableColumn<Student, String> studentTelephoneColumn;
    @FXML
    TableColumn<Student, String> studentEmailColumn;

    @FXML
    ListView<String> updatesListView;


    public void setService(Service service, Teacher teacher) {
        this.service = service;
        this.teacher = teacher;
        initModel();
    }
    public void setDialogStage(Stage stage) {
        this.stage = stage;
    }

    @FXML
    private void initialize() {
        courseTableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
        if (newSelection != null) {
            populateCourseFields(newSelection);
            loadStudentsForCourse(newSelection);
        }
        });
    }

    private void initModel() {
        welcomeLabel.setText("Welcome, " + teacher.getFirstname() + " " + teacher.getLastname() + "!");

        for (CourseCategory category : CourseCategory.values()) {
            String displayValue;
                switch (category) {
                    case under_10_years -> displayValue = "< 10 years";
                    case between_10_and_18_years -> displayValue = "10-18 years";
                    case between_18_and_25_years -> displayValue = "18-25 years";
                    case over_25_years -> displayValue = "> 25 years";
                    default -> displayValue = category.toString();
                }
            ageComboBox.getItems().add(displayValue);
        }

        for (ExperienceLevel level : ExperienceLevel.values()) {
            experienceComboBox.getItems().add(level.toString());
        }

        if (courseNameColumn.getCellValueFactory() == null) {
            courseNameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getName()));
            courseDateColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getDate().format(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm"))));
            courseDurationColumn.setCellValueFactory(cellData -> new SimpleStringProperty(String.valueOf(cellData.getValue().getDuration())));
            coursePriceColumn.setCellValueFactory(cellData -> new SimpleStringProperty(String.valueOf(cellData.getValue().getPrice())));
            courseCategoryColumn.setCellValueFactory(cellData -> {
                CourseCategory category = cellData.getValue().getCategory();
                String displayValue;
                switch (category) {
                    case under_10_years -> displayValue = "< 10 years";
                    case between_10_and_18_years -> displayValue = "10-18 years";
                    case between_18_and_25_years -> displayValue = "18-25 years";
                    case over_25_years -> displayValue = "> 25 years";
                    default -> displayValue = category.toString();
                }
                return new SimpleStringProperty(displayValue);
            });
            courseExperienceLevelColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getExperienceLevel().toString()));
            courseMaxParticipantsColumn.setCellValueFactory(cellData -> new SimpleStringProperty(String.valueOf(cellData.getValue().getMaxParticipants())));
        }

        Iterable<Course> courses = service.getAllCoursesByTeacher(teacher.getId());
        courses.forEach(courseList::add);
        courseTableView.setItems(courseList);


    }

    private void populateCourseFields(Course course) {
        courseNameField.setText(course.getName());
        courseDateField.setText(course.getDate().format(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm")));
        courseDurationField.setText(String.valueOf(course.getDuration()));
        coursePriceField.setText(String.valueOf(course.getPrice()));
        courseMaxParticipantsField.setText(String.valueOf(course.getMaxParticipants()));
        CourseCategory category = course.getCategory();
        String categoryDisplay = switch (category) {
            case under_10_years -> "< 10 years";
            case between_10_and_18_years -> "10-18 years";
            case between_18_and_25_years -> "18-25 years";
            case over_25_years -> "> 25 years";
            default -> category.toString();
        };
        ageComboBox.getSelectionModel().select(categoryDisplay);

        experienceComboBox.getSelectionModel().select(course.getExperienceLevel().toString());
    }

    @FXML
    private void handleAddButton(){
        String name = courseNameField.getText();
        if(name.isEmpty()){
            showAlert("Error", "Please enter a course name!", Alert.AlertType.ERROR);
            return;
        }
        LocalDateTime date;
        try {
            date = LocalDateTime.parse(courseDateField.getText(), DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm"));
        }
        catch (Exception e) {
            showAlert("Invalid date format", "Please enter the date in the format dd/MM/yyyy HH:mm", Alert.AlertType.ERROR);
            return;
        }
        int duration = Integer.parseInt(courseDurationField.getText());
        float price = Float.parseFloat(coursePriceField.getText());
        String selectedCategory = ageComboBox.getSelectionModel().getSelectedItem();
        CourseCategory category = switch (selectedCategory) {
            case "< 10 years" -> CourseCategory.under_10_years;
            case "10-18 years" -> CourseCategory.between_10_and_18_years;
            case "18-25 years" -> CourseCategory.between_18_and_25_years;
            case "> 25 years" -> CourseCategory.over_25_years;
            default -> throw new IllegalArgumentException("Unknown category: " + selectedCategory);
        };
        ExperienceLevel experienceLevel = ExperienceLevel.valueOf(experienceComboBox.getSelectionModel().getSelectedItem());
        int maxParticipants = Integer.parseInt(courseMaxParticipantsField.getText());
        if(name.isEmpty() || date == null || duration <= 0 || price <= 0 || maxParticipants <= 0 || selectedCategory == null || experienceLevel == null) {
            showAlert("Error", "Please fill in all fields correctly!", Alert.AlertType.ERROR);
            return;
        }
        Course course = new Course(name, date, duration, price, category, teacher, experienceLevel, maxParticipants);
        course = service.addCourse(course);

        clearFields();
        showAlert("Course added", "Course added successfully!", Alert.AlertType.INFORMATION);
    }

    @FXML
    private void handleUpdateButton() {
        Course selectedCourse = courseTableView.getSelectionModel().getSelectedItem();
        if (selectedCourse == null) {
            showAlert("Error", "Please select a course to update!", Alert.AlertType.ERROR);
            return;
        }

        int selectedCourseId = selectedCourse.getId();

        String name = courseNameField.getText();
        LocalDateTime date;
        try {
            date = LocalDateTime.parse(courseDateField.getText(), DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm"));
        } catch (Exception e) {
            showAlert("Invalid date format", "Please enter the date in the format dd/MM/yyyy HH:mm", Alert.AlertType.ERROR);
            return;
        }
        int duration = Integer.parseInt(courseDurationField.getText());
        float price = Float.parseFloat(coursePriceField.getText());
        String selectedCategory = ageComboBox.getSelectionModel().getSelectedItem();
        CourseCategory category = switch (selectedCategory) {
            case "< 10 years" -> CourseCategory.under_10_years;
            case "10-18 years" -> CourseCategory.between_10_and_18_years;
            case "18-25 years" -> CourseCategory.between_18_and_25_years;
            case "> 25 years" -> CourseCategory.over_25_years;
            default -> throw new IllegalArgumentException("Unknown category: " + selectedCategory);
        };
        ExperienceLevel experienceLevel = ExperienceLevel.valueOf(experienceComboBox.getSelectionModel().getSelectedItem());
        int maxParticipants = Integer.parseInt(courseMaxParticipantsField.getText());

        if (name.isEmpty() || date == null || duration <= 0 || price <= 0 || maxParticipants <= 0 || selectedCategory == null || experienceLevel == null) {
            showAlert("Error", "Please fill in all fields correctly!", Alert.AlertType.ERROR);
            return;
        }

        service.updateCourse(selectedCourse, name, date, duration, price, category, experienceLevel, maxParticipants);
        int index = courseList.indexOf(selectedCourse);
        courseList.set(index, selectedCourse);
        courseTableView.refresh();


        showAlert("Course updated", "Course updated successfully!", Alert.AlertType.INFORMATION);
    }


    @FXML
    private void handleDeleteButton(){
        Course course = courseTableView.getSelectionModel().getSelectedItem();
        if (course != null) {
            Iterable<Student> students = service.getAllStudentsByCourseAndTeacher(course.getId(), teacher.getId());
            if (students.iterator().hasNext()) {
                showAlert("Cannot delete", "This course has bookings and cannot be deleted!", Alert.AlertType.WARNING);
                return;
            }
            service.deleteCourse(course.getId());
            courseList.remove(course);
            courseTableView.refresh();
            clearFields();
            showAlert("Course deleted", "Course deleted successfully!", Alert.AlertType.INFORMATION);
        } else {
            showAlert("Error", "Please select a course to delete!", Alert.AlertType.ERROR);
        }
    }

    @FXML
    private void handleLogoutButton() {
        stage.close();
        service.removeObserver(this);
        showAlert("Logout", "See you again! <3", Alert.AlertType.INFORMATION);
    }

    private void clearFields(){
        courseNameField.clear();
        courseDateField.clear();
        courseDurationField.clear();
        coursePriceField.clear();
        courseMaxParticipantsField.clear();
        ageComboBox.getSelectionModel().clearSelection();
        experienceComboBox.getSelectionModel().clearSelection();
    }

    private void showAlert(String title, String message, Alert.AlertType type){
        Alert alert = new Alert(type);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    @Override
    public void update(EntityChangeEvent<?> event) {
        ChangeEventType type = event.getType();
        if (type == ChangeEventType.ADDCOURSE ||
                type == ChangeEventType.UPDATECOURSE ||
                type == ChangeEventType.DELETECOURSE ||
                type == ChangeEventType.BOOKCOURSE ||
                type == ChangeEventType.REMOVEBOOKING) {
            refreshCoursesForTeacher();
            Course oldSelected = courseTableView.getSelectionModel().getSelectedItem();
            if (oldSelected != null) {
                for (Course course : courseList) {
                    if (course.getId().equals(oldSelected.getId())) {
                        courseTableView.getSelectionModel().select(course);
                        loadStudentsForCourse(course);
                        break;
                    }
                }
            }
        }
    }
    private void refreshCoursesForTeacher() {
        courseList.clear();
        service.getAllCoursesByTeacher(teacher.getId()).forEach(courseList::add);
        courseTableView.refresh();
    }

    private void loadStudentsForCourse(Course course) {
        studentList.clear();
        Iterable<Student> students = service.getAllStudentsByCourseAndTeacher(course.getId(), teacher.getId());
        students.forEach(studentList::add);
        studentFirstNameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getFirstname()));
        studentLastNameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getLastname()));
        studentAgeColumn.setCellValueFactory(cellData ->
            new SimpleStringProperty(String.valueOf(cellData.getValue().getAge()))
        );
        studentTelephoneColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getPhoneNumber()));
        studentEmailColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getEmail()));
        studentTableView.setItems(studentList);
    }


}
