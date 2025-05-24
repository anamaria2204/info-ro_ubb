package atelier.atelier_de_origami.repository.hibernate;

import atelier.atelier_de_origami.domain.Booking;
import atelier.atelier_de_origami.domain.Course;
import atelier.atelier_de_origami.domain.Student;
import atelier.atelier_de_origami.domain.Teacher;
import atelier.atelier_de_origami.repository.IBooking;
import atelier.atelier_de_origami.repository.ICourseRepo;
import atelier.atelier_de_origami.repository.IStudentRepo;
import atelier.atelier_de_origami.repository.ITeacherRepo;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.query.Query;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class BookingHibernateRepo implements IBooking {

    private final ITeacherRepo teacherRepo;
    private final IStudentRepo studentRepo;
    private final ICourseRepo courseRepo;

    public BookingHibernateRepo(ITeacherRepo teacherRepo, IStudentRepo studentRepo, ICourseRepo courseRepo) {
        this.teacherRepo = teacherRepo;
        this.studentRepo = studentRepo;
        this.courseRepo = courseRepo;
    }

    @Override
    public Booking save(Booking booking) {
        Transaction transaction = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            transaction = session.beginTransaction();
            session.persist(booking);
            transaction.commit();
            return booking;
        } catch (Exception e) {
            if (transaction != null) {
                transaction.rollback();
            }
            throw new RuntimeException("Failed to save booking", e);
        }
    }

    @Override
    public Booking delete(int id) {
        Transaction transaction = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            transaction = session.beginTransaction();
            Booking booking = session.get(Booking.class, id);
            if (booking != null) {
                session.delete(booking);
            }
            transaction.commit();
            return booking;
        } catch (Exception e) {
            if (transaction != null) {
                transaction.rollback();
            }
            throw new RuntimeException("Failed to delete booking with id: " + id, e);
        }
    }

    @Override
    public Booking update(Booking booking) {
        Transaction transaction = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            transaction = session.beginTransaction();
            session.update(booking);
            transaction.commit();
            return booking;
        } catch (Exception e) {
            if (transaction != null) {
                transaction.rollback();
            }
            throw new RuntimeException("Failed to update booking", e);
        }
    }

    @Override
    public Iterable<Booking> findAllBookingsStudent(int idStudent) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Query<Booking> query = session.createQuery(
                "SELECT b FROM Booking b " +
                "JOIN FETCH b.student " +
                "JOIN FETCH b.teacher " +
                "JOIN FETCH b.course " +
                "WHERE b.student.id = :studentId", Booking.class);
            query.setParameter("studentId", idStudent);
            return query.list();
        } catch (Exception e) {
            throw new RuntimeException("Failed to find bookings for student with id: " + idStudent, e);
        }
    }

    @Override
    public Iterable<Booking> findAllBookingsTeacher(int idTeacher) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Query<Booking> query = session.createQuery(
                    "FROM Booking WHERE teacher.id = :teacherId", Booking.class);
            query.setParameter("teacherId", idTeacher);
            return query.list();
        } catch (Exception e) {
            throw new RuntimeException("Failed to find bookings for teacher with id: " + idTeacher, e);
        }
    }

    @Override
    public Iterable<Booking> findAllBookingsCourse(int idCourse) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Query<Booking> query = session.createQuery(
                    "FROM Booking WHERE course.id = :courseId", Booking.class);
            query.setParameter("courseId", idCourse);
            return query.list();
        } catch (Exception e) {
            throw new RuntimeException("Failed to find bookings for course with id: " + idCourse, e);
        }
    }

    @Override
    public Optional<Booking> findOne(Integer id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Booking booking = session.get(Booking.class, id);
            return Optional.ofNullable(booking);
        } catch (Exception e) {
            throw new RuntimeException("Failed to find booking with id: " + id, e);
        }
    }

    @Override
    public Iterable<Booking> findAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Query<Booking> query = session.createQuery("FROM Booking", Booking.class);
            return query.list();
        } catch (Exception e) {
            throw new RuntimeException("Failed to retrieve all bookings", e);
        }
    }

    @Override
    public List<Student> findAllStudentsByCourseAndTeacher(int courseId, int teacherId) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Query<Student> query = session.createQuery(
                "SELECT DISTINCT b.student FROM Booking b " +
                "WHERE b.course.id = :courseId AND b.teacher.id = :teacherId", Student.class);
            query.setParameter("courseId", courseId);
            query.setParameter("teacherId", teacherId);
            return query.list();
        } catch (Exception e) {
            throw new RuntimeException("Failed to find students for course ID " + courseId +
                                       " and teacher ID " + teacherId, e);
        }
    }
}