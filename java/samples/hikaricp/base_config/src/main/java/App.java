import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.sql.DataSource;
import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;
import java.util.Properties;

public class App
{
    private static final String propertiesFile = "build/resources/main/sample.properties";

    public static HikariConfig getHikariConfigFromProperties()
    {
        HikariConfig config = new HikariConfig(propertiesFile);
        return config;
    }

    public static HikariConfig getHikariConfigProperties()
    {
        Properties props = new Properties();
        props.setProperty("jdbcUrl", "jdbc:postgresql://localhost/testdb");
        props.setProperty("dataSource.user", "ubuntu");
        props.setProperty("dataSource.password", "password");

        HikariConfig config = new HikariConfig(props);
        return config;
    }

    public static HikariConfig getHikariConfig()
    {
        HikariConfig config = new HikariConfig();

        config.setJdbcUrl("jdbc:postgresql://localhost/testdb");
        config.setUsername("ubuntu");
        config.setPassword("password");
        //config.addDataSourceProperty("prepStmtCacheSqlLimit", "2048");
        config.addDataSourceProperty("foobar", "2048");

        config.setMaximumPoolSize(8);

        return config;
    }

    public static void main(String[] args)
    {
        //HikariConfig config = new HikariConfig();
        HikariConfig config = getHikariConfigFromProperties();
        //HikariConfig config = getHikariConfig();
        //HikariConfig config = getHikariConfigProperties();
        System.out.println("maximumPoolSize: " + config.getMaximumPoolSize());

        HikariDataSource ds = new HikariDataSource(config);

        //HikariDataSource ds = new HikariDataSource();
        //ds.setJdbcUrl("jdbc:postgresql://localhost/testdb");
        //ds.setUsername("ubuntu");
        //ds.setPassword("password");

        Connection conn = null;
        Statement stmt = null;

        try
        {
            conn = ds.getConnection();

            stmt = conn.createStatement();

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
        finally {
            try {
                if (stmt != null)
                    stmt.close();
            }
            catch (SQLException se2)
            {
                try
                {
                    if (conn != null)  conn.close();
                }
                catch (SQLException e2)
                {
                    e2.printStackTrace();
                }
            }
        }
    }
}
