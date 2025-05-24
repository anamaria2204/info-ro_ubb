module atelier.atelier_de_origami {
    requires javafx.controls;
    requires javafx.fxml;
    requires jakarta.persistence;
    requires com.google.gson;
    requires jakarta.validation;
    requires org.hibernate.orm.core;
    requires org.apache.logging.log4j;
    opens atelier.atelier_de_origami to javafx.fxml;
    exports atelier.atelier_de_origami;
    requires java.naming;

}