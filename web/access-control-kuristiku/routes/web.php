<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| This file is where you may define all of the routes that are handled
| by your application. Just tell Laravel the URIs it should respond
| to using a Closure or controller method. Build something great!
|
*/

Auth::routes();

// First time setup
Route::get('/setup', ['middleware' => 'admincheck', 'uses' => 'RegisterAdminController@index']);

// Logged in user
Route::get('/', 'DashboardController@index');



//Route::get('/accounts', 'HomeController@accounts');
//Route::get('/cards', 'HomeController@cards');
//Route::get('/userSettings', 'HomeController@userSettings');
