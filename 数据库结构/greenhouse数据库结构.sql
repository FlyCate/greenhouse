/*
SQLyog Enterprise v12.09 (64 bit)
MySQL - 5.6.17 : Database - greenhouse
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`greenhouse` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `greenhouse`;

/*Table structure for table `co2` */

DROP TABLE IF EXISTS `co2`;

CREATE TABLE `co2` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime DEFAULT NULL,
  `data` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

/*Data for the table `co2` */

/*Table structure for table `hum` */

DROP TABLE IF EXISTS `hum`;

CREATE TABLE `hum` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime DEFAULT NULL,
  `data` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=gb2312;

/*Data for the table `hum` */

insert  into `hum`(`id`,`time`,`data`) values (1,'2016-10-10 11:32:44',40),(2,'2016-10-10 11:36:05',40.48);

/*Table structure for table `light` */

DROP TABLE IF EXISTS `light`;

CREATE TABLE `light` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime NOT NULL,
  `data` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=gb2312;

/*Data for the table `light` */

/*Table structure for table `soil_hum` */

DROP TABLE IF EXISTS `soil_hum`;

CREATE TABLE `soil_hum` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime DEFAULT NULL,
  `data` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

/*Data for the table `soil_hum` */

/*Table structure for table `soil_tmp` */

DROP TABLE IF EXISTS `soil_tmp`;

CREATE TABLE `soil_tmp` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime DEFAULT NULL,
  `data` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

/*Data for the table `soil_tmp` */

/*Table structure for table `temp` */

DROP TABLE IF EXISTS `temp`;

CREATE TABLE `temp` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime DEFAULT NULL,
  `data` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=gb2312;

/*Data for the table `temp` */

insert  into `temp`(`id`,`time`,`data`) values (1,'2016-10-10 11:32:44',29),(2,'2016-10-10 11:36:05',28.17);

/*Table structure for table `wind_direction` */

DROP TABLE IF EXISTS `wind_direction`;

CREATE TABLE `wind_direction` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime DEFAULT NULL,
  `data` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*Data for the table `wind_direction` */

/*Table structure for table `wind_speed` */

DROP TABLE IF EXISTS `wind_speed`;

CREATE TABLE `wind_speed` (
  `id` int(255) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime DEFAULT NULL,
  `data` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

/*Data for the table `wind_speed` */

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
