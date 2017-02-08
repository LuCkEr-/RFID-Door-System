<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Auth::routes();

// Dashboard
Route::get('/', 'DashboardController@index');

// Accounts
Route::get('/accounts', 'AccountsController@index');
Route::get('/accounts/create', 'AccountsController@create');
Route::get('/accounts/import', 'AccountsController@import');
Route::get('/accounts/edit/{id}', 'AccountsController@edit');

// Setup
Route::get('/setup', 'SetupController@Setup') -> middleware('guest');
