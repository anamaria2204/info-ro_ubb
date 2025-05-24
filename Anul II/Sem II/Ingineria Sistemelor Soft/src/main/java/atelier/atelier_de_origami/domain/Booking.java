package atelier.atelier_de_origami.domain;
import jakarta.persistence.*;
import jakarta.validation.constraints.NotNull;

import java.time.LocalDateTime;

@jakarta.persistence.Entity
@Table(name = "booking")
public class Booking extends Entity<Integer>{

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "id_student")
    @NotNull(message = "Student cannot be null")
    private Student student;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "id_teacher")
    @NotNull(message = "Teacher cannot be null")
    private Teacher teacher;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "id_course")
    @NotNull(message = "Course cannot be null")
    private Course course;

    @Column(name = "course_time")
    @NotNull(message = "Course time cannot be null")
    private LocalDateTime courseTime;

    @Column(name = "booking_date")
    @NotNull(message = "Booking date cannot be null")
    private LocalDateTime date;

    public Booking() {
    }

    public Booking(Integer id, Student student, Teacher teacher, Course course, LocalDateTime courseTime, LocalDateTime date) {
        setId(id);
        this.student = student;
        this.teacher = teacher;
        this.course = course;
        this.courseTime = courseTime;
        this.date = date;
    }

    public Booking(Student student, Teacher teacher, Course course,LocalDateTime courseTime, LocalDateTime date) {
        this.student = student;
        this.teacher = teacher;
        this.course = course;
        this.courseTime = courseTime;
        this.date = date;
    }

    public Student getStudent() {
        return student;
    }
    public void setStudent(Student student) {
        this.student = student;
    }
    public Teacher getTeacher() {
        return teacher;
    }
    public void setTeacher(Teacher teacher) {
        this.teacher = teacher;
    }
    public Course getCourse() {
        return course;
    }
    public void setCourse(Course course) {
        this.course = course;
    }
    public LocalDateTime getCourseTime() {
        return courseTime;
    }
    public void setCourseTime(LocalDateTime courseTime) {
        this.courseTime = courseTime;
    }
    public LocalDateTime getDate() {
        return date;
    }
    public void setDate(LocalDateTime date) {
        this.date = date;
    }
}
