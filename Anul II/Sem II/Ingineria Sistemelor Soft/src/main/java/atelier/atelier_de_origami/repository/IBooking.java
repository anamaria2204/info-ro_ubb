package atelier.atelier_de_origami.repository;

import atelier.atelier_de_origami.domain.Booking;
import atelier.atelier_de_origami.domain.Student;

import java.util.List;

public interface IBooking extends IRepository<Integer, Booking> {
    Booking save(Booking booking);
    Booking delete(int id);
    Booking update(Booking booking);
    Iterable<Booking> findAllBookingsStudent(int idStudent);
    Iterable<Booking> findAllBookingsTeacher(int idTeacher);
    Iterable<Booking> findAllBookingsCourse(int idCourse);
    List<Student> findAllStudentsByCourseAndTeacher(int courseId, int teacherId);
}
