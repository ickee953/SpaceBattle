/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

package su.panov.irrlicht;

import java.io.*;
import java.math.BigInteger;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.zip.GZIPInputStream;
import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.os.Environment;

/** Utils functions. */
public class Utils {
	private static final String TAG = Utils.class.getName();

	/** open file */
	public static FileInputStream tryToGetLocalFile(Context ctx, String filename) {
		try {
			FileInputStream fin = ctx.openFileInput(filename);
			return fin;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return null;
		}
	}

	public static void copyAssets(AssetManager assetManager) {
		String[] files = null;
		try {
			files = assetManager.list("");
		} catch (IOException e) {
			Log.e("tag", e.getMessage());
		}
		for(String filename : files) {
			InputStream in = null;
			OutputStream out = null;
			try {
				in = assetManager.open(filename);
				out = new FileOutputStream("/mnt/sdcard/Irrlicht/" + filename);
				copyFile(in, out);
				in.close();
				in = null;
				out.flush();
				out.close();
				out = null;
			} catch(Exception e) {
				Log.e("tag", e.getMessage());
			}
		}
	}

	private static void copyFile(InputStream in, OutputStream out) throws IOException {
		/* byte[] buffer = new byte[1024];
		int read;
		while((read = in.read(buffer)) != -1){
		out.write(buffer, 0, read);
		}*/
		byte buffer[] = new byte[512 * 1024];
		int nbLecture;
		while ((nbLecture = in.read(buffer)) != -1){
			out.write(buffer, 0, nbLecture);
		}
	}

	public static boolean copyFile(File source, File dest){
		try{
			// Declaration et ouverture des flux
			FileInputStream sourceFile = new FileInputStream(source);
			try{
				java.io.FileOutputStream destinationFile = null;
				try{
					destinationFile = new FileOutputStream(dest);
					// Lecture par segment de 0.5Mo
					byte buffer[] = new byte[512 * 1024];
					int nbLecture;
					while ((nbLecture = sourceFile.read(buffer)) != -1){
						destinationFile.write(buffer, 0, nbLecture);
					}
				} finally {
					destinationFile.close();
				}
			} finally {
				sourceFile.close();
			}
		} catch (IOException e){
			e.printStackTrace();
			return false; // Erreur
		}
		return true; // Résultat OK
	}

	/** svg image on sdcard */
	public static void unpackOnSdCard(AssetManager assetManager)throws IOException {
	if (Environment.getExternalStorageState().compareTo(Environment.MEDIA_MOUNTED)==0) {
		File sdcard = Environment.getExternalStorageDirectory();
		String irrlichtPath = sdcard.getAbsoluteFile() + "/Irrlicht";
		File irrlichtDir = new File(irrlichtPath);
		if (irrlichtDir.exists() && !irrlichtDir.isDirectory()) {
			throw new IOException("Irrlicht exists and is not a directory on SD Card");
		} else if (!irrlichtDir.exists()) {
			if(!irrlichtDir.mkdirs()){
				Log.i(TAG, "ERROR: Create Directory failed " + irrlichtPath);
			}
		}
		// Note: /sdcard/irrlicht dir exists
		String[] filenames = assetManager.list("data");
		for(String filename:filenames) {
			InputStream inputStream = null;
			OutputStream outputStream = null;
			try{
				inputStream = assetManager.open("data/" + filename);
				outputStream = new FileOutputStream(irrlichtPath + "/" + filename);
				// copy
				copyFile(inputStream, outputStream);
			} catch(IOException e){
				e.printStackTrace();
			} finally{
				try{
					outputStream.flush();
					outputStream.close();
					inputStream.close();
				}catch(IOException e){
					e.printStackTrace();
				}
			}
			}
		} else {
			throw new IOException("SD Card not available");
		}
	}

	public static boolean isSdCardAvailable() {
		if (Environment.getExternalStorageState().compareTo(Environment.MEDIA_MOUNTED)==0) {
			return true;
		} else {
			return false;
		}
	}


	/** compute md5 */
	public static String getMd5Hash(String input) {
		try {
			MessageDigest md = MessageDigest.getInstance("MD5");
			byte[] messageDigest = md.digest(input.getBytes());
			BigInteger number = new BigInteger(1, messageDigest);
			String md5 = number.toString(16);
			while (md5.length() < 32) {
				md5 = "0" + md5;
			}
			return md5;
		} catch (NoSuchAlgorithmException e) {
			Log.e("MD5", e.getMessage());
			return null;
		}
	}

	/** read binary input stream */
	private static byte[] readBinaryInput(InputStream in) throws IOException {
		ByteArrayOutputStream bo = new ByteArrayOutputStream();
		byte[] tmpStorage = new byte[4096];
		int pos = 0;
		for (int n; (n = in.read(tmpStorage)) != -1;) {
			bo.write(tmpStorage, 0, n);
			pos += n;
		}
		return bo.toByteArray();
	}

	/** read string input stream */
	private static String readStringInput(InputStream in) throws IOException {
		StringBuilder sb = new StringBuilder();

		byte[] buffer = new byte[4096];
		for (int n; (n = in.read(buffer)) != -1;) {
			sb.append(new String(buffer, 0, n));
		}
		
		return sb.toString();
	}

}
