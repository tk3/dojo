import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.sql.DataSource;

import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

public class App
{
	private static DataSource datasource;

	public static DataSource getDataSource()
	{
		if (datasource == null)
		{
			HikariConfig config = new HikariConfig();

			config.setJdbcUrl("jdbc:postgresql://localhost/testdb");
			config.setUsername("ubuntu");
			config.setPassword("password");

			config.setMaximumPoolSize(8);
			config.setAutoCommit(false);

			datasource = new HikariDataSource(config);
		}
		return datasource;
	}

	public static void main(String[] args)
	{
		Connection connection = null;
		PreparedStatement pstmt = null;
		ResultSet resultSet = null;

		try
		{
			DataSource dataSource = App.getDataSource();
			connection = dataSource.getConnection();
			pstmt = connection.prepareStatement("SELECT * FROM books");

			System.out.println("The Connection Object is of Class: " + connection.getClass());

			resultSet = pstmt.executeQuery();
			while (resultSet.next())
			{
				System.out.println(resultSet.getString(1) + "," + resultSet.getString(2) + "," + resultSet.getString(3));
			}

		}
		catch (Exception e)
		{
			try
			{
				connection.rollback();
			}
			catch (SQLException e1)
			{
				e1.printStackTrace();
			}
			e.printStackTrace();
		}
	}
}
