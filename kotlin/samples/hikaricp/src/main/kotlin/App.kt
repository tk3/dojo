package sample

import java.sql.Connection
import java.sql.Statement
import java.sql.ResultSet
import java.sql.SQLException
import javax.sql.DataSource
import com.zaxxer.hikari.HikariConfig
import com.zaxxer.hikari.HikariDataSource

fun getGreeting(): String {
    return "Hello world."
}

fun main(args: Array<String>) {
    val config = HikariConfig()

    config.setJdbcUrl("jdbc:postgresql://localhost/testdb")
    config.setUsername("ubuntu")
    config.setPassword("password")
    config.setMaximumPoolSize(8)

    val ds = HikariDataSource(config)

    var conn : Connection? = null
    var stmt : Statement? = null

    try
    {
        // 3. コネクションプールから、コネクションを取得する
        conn = ds.getConnection()

        // 4. 取得したコネクションを使って、SELECT文を実行する
        // 5. 結果を取得して、画面に表示する
        stmt = conn.createStatement()
        val rs = stmt.executeQuery("SELECT * FROM books")
        while (rs.next())
        {
            System.out.println(rs.getString(1) + "," + rs.getString(2) + "," + rs.getString(3))
        }

        rs.close()
        stmt.close()
        conn.close()

        // 6. コネクションプールを閉じる
        ds.close()
    }
    catch (e: Exception)
    {
        e.printStackTrace()
    }
    finally {
        try {
            if (stmt != null)
                stmt.close()
        }
        catch (se2: SQLException) {
            try {
                if (conn != null)
                    conn.close()
            }
            catch (e2: SQLException) {
                e2.printStackTrace()
            }
        }
    }

    println(getGreeting())
}
