name := "SlickSample"

version := "0.1"

scalaVersion := "2.13.1"

libraryDependencies ++= Seq(
  "org.scalaz" %% "scalaz-core" % "7.2.30",
  "com.typesafe.slick" %% "slick" % "3.3.2",
  "org.slf4j" % "slf4j-nop" % "1.7.25",
  "com.h2database" % "h2" % "1.4.200"
)
