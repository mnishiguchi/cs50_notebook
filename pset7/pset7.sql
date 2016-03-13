-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) NOT NULL,
  `transaction` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `date` timestamp(6) NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `symbol` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(10) NOT NULL,
  `price` decimal(64,0) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (14,'SELL','2014-06-04 14:27:19.910049','SBUX',50,74),(14,'BUY','2014-06-04 14:27:28.942460','SBUX',51,74),(14,'SELL','2014-06-04 14:36:41.097885','WMT',6,77),(14,'BUY','2014-06-04 14:37:26.363960','SBUX',6,74),(14,'SELL','2014-06-04 15:32:41.603288','SBUX',57,74),(14,'BUY','2014-06-04 15:32:53.578913','WMT',50,77),(14,'BUY','2014-06-04 15:36:38.907368','SBUX',5,74),(14,'SELL','2014-06-04 15:36:59.298119','WMT',50,77),(14,'SELL','2014-06-04 15:37:30.178350','TM',50,114),(14,'SELL','2014-06-04 15:37:37.766587','SBUX',5,74),(14,'BUY','2014-06-04 17:48:23.234568','SBUX',50,74),(14,'BUY','2014-06-04 17:48:37.315903','TM',30,115),(14,'BUY','2014-06-04 17:48:53.086133','WMT',30,77),(14,'SELL','2014-06-05 14:59:27.975092','SBUX',50,75),(14,'SELL','2014-06-05 14:59:43.399183','WMT',30,77),(14,'SELL','2014-06-05 14:59:50.012585','TM',30,114),(33,'BUY','2014-06-05 15:02:54.864822','AA',33,14),(33,'BUY','2014-06-05 15:03:13.140867','B',12,37),(33,'BUY','2014-06-05 15:03:22.847539','C',34,48),(33,'BUY','2014-06-05 15:03:35.415634','D',4,70),(33,'BUY','2014-06-05 15:03:48.181063','Z',12,116),(33,'SELL','2014-06-05 15:04:37.285836','AA',33,14),(33,'SELL','2014-06-05 15:04:46.207353','B',12,37),(33,'SELL','2014-06-05 15:04:54.140552','C',34,48),(33,'SELL','2014-06-05 15:04:59.520692','D',4,70),(33,'SELL','2014-06-05 15:05:04.694192','Z',12,117),(33,'BUY','2014-06-05 15:05:59.995366','AMZN',30,316),(33,'SELL','2014-06-05 15:06:43.832480','AMZN',30,316),(33,'BUY','2014-06-05 15:06:58.714949','AMZN',12,316),(33,'SELL','2014-06-05 15:07:36.271402','AMZN',12,316),(14,'BUY','2014-06-05 15:09:03.186382','SBUX',10,74),(14,'BUY','2014-06-05 15:09:13.355164','AMZN',12,317),(32,'BUY','2014-06-05 15:10:28.233172','R',13,86),(32,'BUY','2014-06-05 15:10:41.419463','S',34,9),(32,'BUY','2014-06-05 15:10:52.121030','T',2,35),(32,'BUY','2014-06-05 15:11:22.596178','UA',2,53),(32,'SELL','2014-06-05 15:11:48.398440','R',13,86),(32,'SELL','2014-06-05 15:12:04.946768','S',34,9),(32,'SELL','2014-06-05 15:12:22.077007','UA',2,53);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolio`
--

DROP TABLE IF EXISTS `portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolio` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolio`
--

LOCK TABLES `portfolio` WRITE;
/*!40000 ALTER TABLE `portfolio` DISABLE KEYS */;
INSERT INTO `portfolio` VALUES (1,'SBUX',10),(2,'SBUX',10),(3,'SBUX',10),(4,'SBUX',10),(5,'SBUX',10),(6,'SBUX',10),(7,'SBUX',10),(14,'AMZN',12),(14,'SBUX',10),(32,'T',2);
/*!40000 ALTER TABLE `portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(2,'hirschhorn','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','$1$HA$azTGIMVlmPi9W9Y12cYSj/',10000.0000),(5,'milo','$1$HA$6DHumQaK4GhpX8QE23C8V1',10000.0000),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000),(14,'masa','$1$qklgB93o$jjLrN77x0jbQ1rem2eK/t1',5443.6717),(28,'Christine','$1$FLMCNpac$1vLVP4ENYa9t6hThwSH0d1',10000.0000),(32,'123','$1$oujH7Lio$RX4RhUU.HtlPs4rVjkHgI0',9930.1346),(33,'aaa','$1$PlW.HoLf$dvlVsZeflGIYsg9pIL4yx.',9999.5000);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-06-05 11:14:02
