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
import com.zaxxer.hikari.HikariPoolMXBean;

public class App {
    private static final String JDBC_DRIVER = org.h2.Driver.class.getName();
    private static final String JDBC_URL = "jdbc:h2:mem:test;DB_CLOSE_DELAY=-1";
    private static final String USER = "sa";
    private static final String PASSWORD = "";
    private static final String sqlFile = "build/resources/main/init.sql";

    public static void printBean(HikariDataSource ds)
    {
        HikariPoolMXBean bean = ds.getHikariPoolMXBean();

        System.out.println("Connections: ");
        System.out.println("  Idle: " + bean.getIdleConnections());
        System.out.println("  Active: " + bean.getActiveConnections());
        System.out.println("  Total: " + bean.getTotalConnections());
        System.out.println("  ThreadsAwaiting: " + bean.getThreadsAwaitingConnection());
        System.out.println("");
    }

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

        config.setMaximumPoolSize(3);
        //config.setConnectionTimeout(3000);
        //config.setConnectionTimeout(0);

        HikariDataSource ds = new HikariDataSource(config);

        Connection conn1 = null;
        Connection conn2 = null;
        Connection conn3 = null;
        Statement stmt = null;

        try
        {
            conn1 = ds.getConnection();
            conn2 = ds.getConnection();
            conn3 = ds.getConnection();

            printBean(ds);

            ds.evictConnection(conn2);

            printBean(ds);

            conn1.close();
            conn2.close();
            conn3.close();

            ds.evictConnection(conn3);

            printBean(ds);

            ds.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
