package atelier.atelier_de_origami.repository.hibernate;

import atelier.atelier_de_origami.domain.Course;
import atelier.atelier_de_origami.domain.CourseCategory;
import atelier.atelier_de_origami.domain.ExperienceLevel;
import atelier.atelier_de_origami.domain.Teacher;
import atelier.atelier_de_origami.repository.ICourseRepo;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.query.NativeQuery;
import org.hibernate.query.Query;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class CourseHibernateRepo implements ICourseRepo {
    @Override
    public Course save(String name, LocalDateTime date, int duration, float price,
                     CourseCategory category, Teacher teacher,
                     ExperienceLevel experienceLevel, int maxParticipants) {
        Transaction transaction = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            transaction = session.beginTransaction();

            Course course = new Course(name, date, duration, price,
                                     category, teacher, experienceLevel, maxParticipants);
            session.persist(course);

            transaction.commit();
            return course;
        } catch (Exception e) {
            if (transaction != null) {
                transaction.rollback();
            }
            throw new RuntimeException("Failed to save course", e);
        }
    }

    @Override
    public Course update(Course course, String name, LocalDateTime newDate, int duration,
                       float price, CourseCategory category,
                       ExperienceLevel experienceLevel, int maxParticipants) {
        if (course == null || course.getId() == null) {
            throw new IllegalArgumentException("Course or Course ID must not be null for update.");
        }

        Transaction transaction = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            transaction = session.beginTransaction();
            course.setName(name);
            course.setDate(newDate);
            course.setDuration(duration);
            course.setPrice(price);
            course.setCategory(category);
            course.setExperienceLevel(experienceLevel);
            course.setMaxParticipants(maxParticipants);

            Course updatedCourse = session.merge(course);
            transaction.commit();
            return updatedCourse;
        } catch (Exception e) {
            if (transaction != null) {
                transaction.rollback();
            }
            throw new RuntimeException("Failed to update course", e);
        }
    }

    @Override
    public Course delete(int id) {
        Transaction transaction = null;
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            transaction = session.beginTransaction();

            Course course = session.find(Course.class, id);
            if (course != null) {
                session.remove(course);
            }
            transaction.commit();
            return course;
        } catch (Exception e) {
            if (transaction != null) {
                transaction.rollback();
            }
            throw new RuntimeException("Failed to delete course", e);
        }
    }

    @Override
    public Iterable<Course> findAllCourseTeacher(int idTeacher) {
    try (Session session = HibernateUtils.getSessionFactory().openSession()) {
        NativeQuery<Course> query = session.createNativeQuery(
            "SELECT id, category, " +
            "CAST(date AS BIGINT) as date, " +
            "duration, experiencelevel, maxparticipants, name, price, idTeacher " +
            "FROM course WHERE idTeacher = :teacherId", Course.class);
        query.setParameter("teacherId", idTeacher);
        return query.getResultList();
    } catch (Exception e) {
        throw new RuntimeException("Failed to find courses by teacher ID", e);
    }
}
    @Override
    public Optional findOne(Integer id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Course course = session.find(Course.class, id);
            return Optional.ofNullable(course);
        } catch (Exception e) {
            throw new RuntimeException("Failed to find course by ID", e);
        }
    }

    @Override
    public Iterable<Course> findAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            return session.createQuery("FROM Course", Course.class).list();
        } catch (Exception e) {
            throw new RuntimeException("Failed to retrieve all courses", e);
        }
    }

    @Override
    public Iterable<Course> findCoursesForAge(int age) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            List<CourseCategory> eligibleCategories = new ArrayList<>();

            if (age < 10) {
                eligibleCategories.add(CourseCategory.under_10_years);
            } else if (age < 18) {
                eligibleCategories.add(CourseCategory.between_10_and_18_years);
            } else if (age < 25) {
                eligibleCategories.add(CourseCategory.between_18_and_25_years);
            } else {
                eligibleCategories.add(CourseCategory.over_25_years);
            }

            Query<Course> query = session.createQuery(
                "SELECT c FROM Course c JOIN FETCH c.teacher WHERE c.category IN (:categories)", Course.class);
            query.setParameter("categories", eligibleCategories);

            return query.getResultList();
        } catch (Exception e) {
            throw new RuntimeException("Failed to retrieve courses for age " + age, e);
        }
    }


}
