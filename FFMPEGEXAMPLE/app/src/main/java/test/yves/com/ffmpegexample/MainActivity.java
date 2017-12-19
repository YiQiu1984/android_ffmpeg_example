package test.yves.com.ffmpegexample;

import android.Manifest;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private final String VIDEO_PATH = "/sdcard/Downloads/";
    private final String VIDEO_NAME = "transformers3";
    private final String VIDEO_SUFFIX_FLV = ".flv";
    private final String VIDEO_SUFFIX_MP4 = ".mp4";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avdevice-57");
        System.loadLibrary("avfilter-6");
        System.loadLibrary("avformat-57");
        System.loadLibrary("avresample-3");
        System.loadLibrary("avutil-55");
        System.loadLibrary("postproc-54");
        System.loadLibrary("swresample-2");
        System.loadLibrary("swscale-4");
        System.loadLibrary("native-lib");
    }

    private static final int REQUEST_EXTERNAL_STORAGE = 1;
    private static String[] PERMISSIONS_STORAGE = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    private RelativeLayout mProgressBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        int permission = ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE);
        if (permission != PackageManager.PERMISSION_GRANTED) {
            // We don't have permission so prompt the user
            ActivityCompat.requestPermissions(
                    this,
                    PERMISSIONS_STORAGE,
                    REQUEST_EXTERNAL_STORAGE
            );
        }

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        mProgressBar = (RelativeLayout) findViewById(R.id.progressBar);

        String filepath = VIDEO_PATH + VIDEO_NAME + VIDEO_SUFFIX_FLV;
        File file = new File(filepath);
        if (file.exists()) {
            Log.i("ffmpeg", "ffmpeg file is exists=" +file.getAbsolutePath());
        } else {
            Log.i("ffmpeg", "ffmpeg file is not exists");
            Toast.makeText(this, "file input to transcoding is not exist", Toast.LENGTH_SHORT).show();
            return;
        }


        mProgressBar.setVisibility(View.VISIBLE);
        new Thread(new Runnable() {
            @Override
            public void run() {
                ffmpegcore(8, getTransforCommend());
                Log.i("ffmpeg", "fffmpegcore run end");
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        mProgressBar.setVisibility(View.GONE);
                        String output = VIDEO_PATH + VIDEO_NAME + VIDEO_SUFFIX_MP4;
                        Toast.makeText(MainActivity.this, "transcoding finish, output=" +output,
                                Toast.LENGTH_SHORT).show();
                    }
                });
            }
        }).start();
    }


    private String[] getTransforCommend() {
        String[] commands = new String[8];
        commands[0] = "ffmpeg";
        commands[1] = "-i";
        commands[2] = VIDEO_PATH + VIDEO_NAME + VIDEO_SUFFIX_FLV;
        commands[3] = "-vcodec";
        commands[4] = "libx264";
        commands[5] = "-acodec";
        commands[6] = "aac";
        commands[7] = VIDEO_PATH + VIDEO_NAME + VIDEO_SUFFIX_MP4;

        return commands;
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int ffmpegcore(int argc, String[] argv);
    public native int ffmpegrun(String[] argv);
}
