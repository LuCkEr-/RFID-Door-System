@extends('layouts.authenticate')

@section('authTitle', 'Login')

@section('authBody')
<form class="form" role="form" method="POST" action="{{ url('/login') }}">
    {{ csrf_field() }}

        <div class="form-group{{ $errors->has('email') ? ' has-error' : '' }}">
            <input id="email" type="email" class="form-control" name="email" value="{{ old('email') }}" placeholder="E-mail" required autofocus>

            @if ($errors->has('email'))
                <span class="help-block">
                    <strong>{{ $errors->first('email') }}</strong>
                </span>
            @endif
        </div>

        <div class="form-group{{ $errors->has('password') ? ' has-error' : '' }}">
            <input id="password" type="password" class="form-control" name="password" placeholder="Password" required>

            @if ($errors->has('password'))
                <span class="help-block">
                    <strong>{{ $errors->first('password') }}</strong>
                </span>
            @endif
        </div>

        <div class="checkbox">
            <label>
                <input type="checkbox" name="remember" {{ old('remember') ? 'checked' : ''}}> Remember Me
            </label>
        </div>

        <div class="form-group">
            <button type="submit" class="btn btn-lg btn-success btn-block">
                Login
            </button>
        </div>

        <a class="btn btn-link btn-block" href="{{ url('/password/reset') }}">
            Forgot Your Password?
        </a>
</form>
@endsection
