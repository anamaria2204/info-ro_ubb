package atelier.atelier_de_origami.service;

import atelier.atelier_de_origami.domain.*;
import atelier.atelier_de_origami.events.ChangeEventType;
import atelier.atelier_de_origami.events.EntityChangeEvent;
import atelier.atelier_de_origami.observer.Observable;
import atelier.atelier_de_origami.observer.Observer;
import atelier.atelier_de_origami.repository.IBooking;
import atelier.atelier_de_origami.repository.ICourseRepo;
import atelier.atelier_de_origami.repository.IStudentRepo;
import atelier.atelier_de_origami.repository.ITeacherRepo;

import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Service implements IService, Observable<EntityChangeEvent<?>> {

    private final IStudentRepo studentRepo;
    private final ITeacherRepo teacherRepo;
    private final ICourseRepo courseRepo;
    private final IBooking bookingRepo;

    private final List<Observer<EntityChangeEvent<?>>> observers = new ArrayList<>();


    public Service(IStudentRepo studentRepo, ITeacherRepo teacherRepo, ICourseRepo courseRepo, IBooking bookingRepo) {
        this.studentRepo = studentRepo;
        this.teacherRepo = teacherRepo;
        this.courseRepo = courseRepo;
        this.bookingRepo = bookingRepo;
    }
    @Override
    public Iterable<Student> getAllStudents() {
        return studentRepo.findAll();
    }

    @Override
    public Iterable<Teacher> getAllTeachers() {
        return teacherRepo.findAll();
    }

    @Override
    public Iterable<Course> getAllCourses() {
        return courseRepo.findAll();
    }

    @Override
    public Iterable<Course> getAllCoursesByTeacher(int idTeacher) {
        return courseRepo.findAllCourseTeacher(idTeacher);
    }

    @Override
    public Iterable<Course> getAllCoursesForAge(int age) {
        return courseRepo.findCoursesForAge(age);
    }

    @Override
    public Iterable<Course> getAllCoursesBookedByStudent(int idStudent) {
        Iterable<Booking> bookings = bookingRepo.findAllBookingsStudent(idStudent);
        List<Course> courses = new ArrayList<>();
        for (Booking booking : bookings) {
            Course course = booking.getCourse();
            if (course != null) {
                courses.add(course);
            }
        }
        return courses;
    }



    @Override
    public Iterable<Booking> getAllBookingStudent(int idStudent) {
        return bookingRepo.findAllBookingsStudent(idStudent);
    }

    @Override
    public Iterable<Booking> getBookingStudentCourse(int idStudent, int idCourse) {
        Iterable<Booking> bookings = bookingRepo.findAllBookingsStudent(idStudent);
        List<Booking> courseBookings = new ArrayList<>();
        for (Booking booking : bookings) {
            if (booking.getCourse().getId() == idCourse) {
                courseBookings.add(booking);
            }
        }
        return courseBookings;
    }

    @Override
    public Teacher getTeacherByUsername(String username) {
        return teacherRepo.findByUsername(username);
    }

    @Override
    public Student getStudentByUsername(String username) {
        return studentRepo.findByUsername(username);
    }

    @Override
    public Course addCourse(Course course) {
        if (course == null) {
            throw new IllegalArgumentException("Course cannot be null");
        }
        try{
            String name = course.getName();
            LocalDateTime date = course.getDate();
            int duration = course.getDuration();
            float price = course.getPrice();
            CourseCategory category = course.getCategory();
            Teacher teacher = course.getTeacher();
            ExperienceLevel experienceLevel = course.getExperienceLevel();
            int maxParticipants = course.getMaxParticipants();
            if (teacher == null) {
                throw new IllegalArgumentException("Teacher cannot be null");
            }
            Course savedCourse = courseRepo.save(name, date, duration, price, category, teacher, experienceLevel, maxParticipants);

            notifyObservers(new EntityChangeEvent<>(ChangeEventType.ADDCOURSE, savedCourse));
            return savedCourse;
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
        return null;
    }

    @Override
    public Course findCourseById(int id) {
        Optional<Course> courseOpt = courseRepo.findOne(id);
        if (courseOpt.isPresent()) {
            return courseOpt.get();
        } else {
            throw new IllegalArgumentException("Course not found with id: " + id);
        }
    }

    @Override
    public void updateCourse(Course course, String name, LocalDateTime date, int duration, double price, CourseCategory category, ExperienceLevel experienceLevel, int maxParticipants) {
        try {
            course.setName(name);
            course.setDate(date);
            course.setDuration(duration);
            float price_f = (float) price;
            course.setPrice(price_f);
            course.setCategory(category);
            course.setExperienceLevel(experienceLevel);
            course.setMaxParticipants(maxParticipants);
            courseRepo.update(course, name, date, duration, price_f, category, experienceLevel, maxParticipants);
            notifyObservers(new EntityChangeEvent<>(ChangeEventType.UPDATECOURSE, course));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    public void deleteCourse(int id) {
        try{
            Course course = courseRepo.delete(id);
            if (course == null) {
                throw new IllegalArgumentException("Course not found");
            }
            notifyObservers(new EntityChangeEvent<>(ChangeEventType.DELETECOURSE, course));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    public void addStudent(Student student) {
        try{
            String username = student.getUsername();
            String password = student.getPassword();
            if (username == null || password == null) {
                throw new IllegalArgumentException("Username and password cannot be null");
            }
            studentRepo.save(student);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    public void addBooking(Student student, Course course) {
        try{
            if (student == null || course == null) {
                throw new IllegalArgumentException("Student and course cannot be null");
            }

            LocalDateTime courseDate = course.getDate();
            LocalDateTime bookingTime = LocalDateTime.now();
            if (courseDate == null || bookingTime == null) {
                throw new IllegalArgumentException("Course date and booking time cannot be null");
            }
            Teacher teacher = course.getTeacher();
            Booking saved_booking = new Booking(student, teacher, course, courseDate, bookingTime);

            bookingRepo.save(saved_booking);

            course.setMaxParticipants(course.getMaxParticipants() - 1);
            courseRepo.update(course, course.getName(), course.getDate(), course.getDuration(), course.getPrice(), course.getCategory(), course.getExperienceLevel(), course.getMaxParticipants());

            notifyObservers(new EntityChangeEvent<>(ChangeEventType.BOOKCOURSE, saved_booking));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    public void deleteBooking(Student student, Course course) {
        if(student == null || course == null) {
            throw new IllegalArgumentException("Student and course cannot be null");
        }
        try {
            Booking delete_b = getBookingStudentCourse(student.getId(), course.getId()).iterator().next();
            Booking booking = bookingRepo.delete(delete_b.getId());
            if (booking == null) {
                throw new IllegalArgumentException("Booking not found");
            }
            course.setMaxParticipants(course.getMaxParticipants() + 1);
            courseRepo.update(course, course.getName(), course.getDate(), course.getDuration(), course.getPrice(), course.getCategory(), course.getExperienceLevel(), course.getMaxParticipants());

            notifyObservers(new EntityChangeEvent<>(ChangeEventType.REMOVEBOOKING, booking));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    public Iterable<Student> getAllStudentsByCourseAndTeacher(int idCourse, int idTeacher) {
        return bookingRepo.findAllStudentsByCourseAndTeacher(idCourse, idTeacher);
    }


    @Override
    public void addObserver(Observer<EntityChangeEvent<?>> e) {
        System.out.println(">>> Service adaugă observatorul: " + e);
        observers.add(e);

        System.out.println("Observatori curenti:");
        observers.forEach(obs -> System.out.println("  - " + obs));
    }

    @Override
    public void removeObserver(Observer<EntityChangeEvent<?>> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(EntityChangeEvent<?> t) {
        System.out.println(">>> Service notifică observatori despre evenimentul: " + t.getType());
        for (Observer<EntityChangeEvent<?>> observer : observers) {
            observer.update(t);
        }
    }

}
