package atelier.atelier_de_origami.repository.hibernate;

import atelier.atelier_de_origami.domain.*;
import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import org.hibernate.cfg.AvailableSettings;
import org.hibernate.cfg.Configuration;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;


public class HibernateUtils {

    private static SessionFactory sessionFactory;

    public static SessionFactory getSessionFactory(){
        if ((sessionFactory==null)||(sessionFactory.isClosed()))
            sessionFactory=createNewSessionFactory();
        return sessionFactory;
    }

    private static  SessionFactory createNewSessionFactory(){
        try {
            var inputStream = HibernateUtils.class.getClassLoader()
                    .getResourceAsStream("hibernate.properties");

            Properties properties = new Properties();
            properties.load(inputStream);

            Configuration sessionFactory = new Configuration()
                    .addProperties(properties)
                    .addAnnotatedClass(Teacher.class)
                    .addAnnotatedClass(Course.class)
                    .addAnnotatedClass(Student.class)
                    .addAnnotatedClass(Booking.class);
            return sessionFactory.buildSessionFactory();
        } catch (Exception e) {
            throw new RuntimeException("Failed to create SessionFactory", e);
        }
    }

    public static  void closeSessionFactory(){
        if (sessionFactory!=null)
            sessionFactory.close();
    }
}