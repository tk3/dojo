import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.sql.DataSource;
import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

public class App
{
	public static void main(String[] args)
	{
		HikariConfig config = new HikariConfig();

		config.setJdbcUrl("jdbc:postgresql://localhost/testdb");
		config.setUsername("ubuntu");
		config.setPassword("password");

		config.setMaximumPoolSize(8);

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
		finally {
			try {
				if (stmt != null)
					stmt.close();
			}
			catch (SQLException se2) {
				try {
					if (conn != null)
						conn.close();
				}
				catch (SQLException e2) {
					e2.printStackTrace();
				}
			}
		}
	}
}
