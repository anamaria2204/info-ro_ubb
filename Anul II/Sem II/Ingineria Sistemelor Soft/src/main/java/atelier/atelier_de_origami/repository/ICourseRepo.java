package atelier.atelier_de_origami.repository;

import atelier.atelier_de_origami.domain.Course;
import atelier.atelier_de_origami.domain.CourseCategory;
import atelier.atelier_de_origami.domain.ExperienceLevel;
import atelier.atelier_de_origami.domain.Teacher;

import java.time.LocalDateTime;

public interface ICourseRepo extends IRepository<Integer, Course>{
    Course save(String name, LocalDateTime date, int duration, float price, CourseCategory category, Teacher teacher, ExperienceLevel experienceLevel, int maxParticipants);
    Course update(Course course,String name, LocalDateTime time, int duration, float price, CourseCategory category, ExperienceLevel experienceLevel, int maxParticipants);
    Course delete(int id);
    Iterable<Course> findAllCourseTeacher(int idTeacher);
    Iterable<Course> findCoursesForAge(int age);
}
