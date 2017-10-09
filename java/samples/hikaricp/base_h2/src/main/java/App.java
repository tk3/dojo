import org.h2.jdbcx.JdbcDataSource;
import org.h2.tools.RunScript;
import java.sql.SQLException;
import java.nio.charset.StandardCharsets;

import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.sql.DataSource;
import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

public class App {
    private static final String JDBC_DRIVER = org.h2.Driver.class.getName();
    private static final String JDBC_URL = "jdbc:h2:mem:test;DB_CLOSE_DELAY=-1";
    private static final String USER = "sa";
    private static final String PASSWORD = "";
    private static final String sqlFile = "build/resources/main/init.sql";

    public static void main(String[] args) {
        try {
            RunScript.execute(JDBC_URL, USER, PASSWORD, sqlFile, StandardCharsets.UTF_8, false);
        }
        catch (SQLException e) {
        }
        System.out.println("");

        HikariConfig config = new HikariConfig();

        config.setJdbcUrl(JDBC_URL);
        config.setUsername("sa");
        config.setPassword("");

        config.setMaximumPoolSize(8);
        config.setAutoCommit(false);

        HikariDataSource ds = new HikariDataSource(config);

        Connection conn = null;
        Statement stmt = null;

        try
        {
            conn = ds.getConnection();

            stmt = conn.createStatement();

            System.out.println("The Connection Object is of Class: " + conn.getClass());

            ResultSet rs = stmt.executeQuery("SELECT * FROM books");
            while (rs.next())
            {
                System.out.println(rs.getString(1) + "," + rs.getString(2) + "," + rs.getString(3));
            }

            rs.close();
            stmt.close();
            conn.close();

            ds.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
