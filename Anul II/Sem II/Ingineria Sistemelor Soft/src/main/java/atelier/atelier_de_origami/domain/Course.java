package atelier.atelier_de_origami.domain;

import jakarta.persistence.*;
import jakarta.validation.constraints.*;

import java.time.LocalDateTime;

@jakarta.persistence.Entity
@Table(name = "course")
public class Course extends Entity<Integer> {

    @Column(name = "name")
    @NotBlank(message = "Name is required")
    @Size(max = 100, message = "Name must be less than 100 characters")
    private String name;

    @Convert(converter = TimestampStringConverter.class)
    @Column(name = "date", columnDefinition = "VARCHAR(255)")    @Future(message = "Course date must be in the future")
    @NotNull(message = "Date is required")
    private LocalDateTime date;

    @Column(name = "duration")
    @Positive(message = "Duration must be positive")
    private int duration;

    @Column(name = "price")
    @PositiveOrZero(message = "Price cannot be negative")
    private float price;

    @Column(name = "category")
    @NotNull(message = "Category is required")
    private CourseCategory category;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "idTeacher")
    @NotNull(message = "Teacher is required")
    private Teacher teacher;

    @Column(name = "experiencelevel")
    @NotNull(message = "Experience level is required")
    private ExperienceLevel experienceLevel;


    @Column(name = "maxparticipants")
    @Min(value = 0, message = "Max participants must be at least 0")
    private int maxParticipants;

    public Course() {
    }

    public Course(int id, String name, LocalDateTime date, int duration, float price, CourseCategory category, Teacher teacher, ExperienceLevel experienceLevel, int maxParticipants) {
        setId(id);
        this.name = name;
        this.date = date;
        this.duration = duration;
        this.price = price;
        this.category = category;
        this.teacher = teacher;
        this.experienceLevel = experienceLevel;
        this.maxParticipants = maxParticipants;
    }

    public Course(String name, LocalDateTime date, int duration, float price, CourseCategory category, Teacher teacher, ExperienceLevel experienceLevel, int maxParticipants) {
        this.name = name;
        this.date = date;
        this.duration = duration;
        this.price = price;
        this.category = category;
        this.teacher = teacher;
        this.experienceLevel = experienceLevel;
        this.maxParticipants = maxParticipants;
    }

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public LocalDateTime getDate() {
        return date;
    }
    public void setDate(LocalDateTime date) {
        this.date = date;
    }
    public int getDuration() {
        return duration;
    }
    public void setDuration(int duration) {
        this.duration = duration;
    }
    public float getPrice() {
        return price;
    }
    public void setPrice(float price) {
        this.price = price;
    }
    public CourseCategory getCategory() {
        return category;
    }
    public void setCategory(CourseCategory category) {
        this.category = category;
    }
    public Teacher getTeacher() {
        return teacher;
    }
    public void setTeacher(Teacher teacher) {
        this.teacher = teacher;
    }
    public ExperienceLevel getExperienceLevel() {
        return experienceLevel;
    }
    public void setExperienceLevel(ExperienceLevel experienceLevel) {
        this.experienceLevel = experienceLevel;
    }
    public int getMaxParticipants() {
        return maxParticipants;
    }
    public void setMaxParticipants(int maxParticipants) {
        this.maxParticipants = maxParticipants;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Course course = (Course) o;
        return getId() != null && getId().equals(course.getId());
    }

    @Override
    public int hashCode() {
        return getId() != null ? getId().hashCode() : 0;
    }

}
