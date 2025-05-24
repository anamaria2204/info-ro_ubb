package atelier.atelier_de_origami.domain;

import jakarta.persistence.*;
import java.time.*;
import java.util.Objects;

@Converter(autoApply = true)
public class TimestampStringConverter implements AttributeConverter<LocalDateTime, String> {
    @Override
    public String convertToDatabaseColumn(LocalDateTime attribute) {
        if (attribute == null) return null;
        return String.valueOf(attribute.atZone(ZoneId.systemDefault()).toInstant().toEpochMilli());
    }

    @Override
    public LocalDateTime convertToEntityAttribute(String dbData) {
        if (dbData == null || dbData.trim().isEmpty()) return null;
        try {
            long millis = Long.parseLong(dbData);
            return LocalDateTime.ofInstant(Instant.ofEpochMilli(millis), ZoneId.systemDefault());
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Invalid timestamp value in database: " + dbData);
        }
    }
}
