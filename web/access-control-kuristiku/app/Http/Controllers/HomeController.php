<?php

namespace KAC\Http\Controllers;

use Illuminate\Http\Request;
use KAC;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Auth;

class HomeController extends Controller
{
    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('auth');
    }

    /**
     * Show the application dashboard.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        return view('pages.dashboard');
    }

    public function accounts()
    {
        $users = KAC\User::all();
        return view('pages.accounts', ['users' => $users]);
    }

    public function cards()
    {
        $cards = KAC\rfidCards::all();
        return view('pages.cards', ['cards' => $cards]);
    }

    public function userSettings()
    {
        $user = DB::table('users')
        -> select('name', 'email')
        -> where('email', Auth::user() -> email)
        -> limit(1)
        -> get();
        return view('pages.userSettings', ['user' => $user]);
    }
}
