package atelier.atelier_de_origami.service;

import atelier.atelier_de_origami.domain.*;

import java.time.LocalDateTime;

public interface IService {
    Iterable<Student> getAllStudents();
    Iterable<Teacher> getAllTeachers();
    Iterable<Course> getAllCourses();
    Iterable<Course> getAllCoursesByTeacher(int idTeacher);
    Iterable<Course> getAllCoursesForAge(int age);
    Iterable<Course> getAllCoursesBookedByStudent(int idStudent);
    Iterable<Booking> getAllBookingStudent(int idStudent);
    Iterable<Booking> getBookingStudentCourse(int idStudent, int idCourse);
    Iterable<Student> getAllStudentsByCourseAndTeacher(int idCourse, int idTeacher);
    Teacher getTeacherByUsername(String username);
    Student getStudentByUsername(String username);
    Course addCourse(Course course);
    Course findCourseById(int id);
    void updateCourse(Course course, String name, LocalDateTime date, int duration, double price, CourseCategory category, ExperienceLevel experienceLevel, int maxParticipants);
    void deleteCourse(int id);
    void addStudent(Student student);
    void addBooking(Student student, Course course);
    void deleteBooking(Student student, Course course);

}
